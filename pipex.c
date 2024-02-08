/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marde-vr <marde-vr@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 20:26:11 by marde-vr          #+#    #+#             */
/*   Updated: 2024/02/08 19:29:18 by marde-vr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft/libft.h"
#include <unistd.h>

int ft_exit(t_pipex *pipex, int error_code)
{
	// called when done done executing or if a malloc failed
	// clean struct:
	// - close all FDs (in_fd and out_fd)
	// - free all allocated memory
	// - potentially remove the temporary here_doc file using unlink
	
	if (error_code)
		perror("Error");
	if (pipex)
	{
		if (pipex->cmd_args)
			free(pipex->cmd_paths);
		if (pipex->cmd_args)
		{
			int i = 0;
			while (i < pipex->cmd_count)
			{
				int j = 0;
				while (pipex->cmd_args[i][j])
				{
					free(pipex->cmd_args[i][j]);
					j++;
				}
				free(pipex->cmd_args[i]);
				i++;
			}
		}
	}
	free(pipex);
	return (0);
}

int	init_pipex(t_pipex **pipex, int argc, char **argv)
{
	*pipex = ft_calloc(1, sizeof(t_pipex));
	if (!*pipex)
		return (1);
	(*pipex)->in_fd = 0;
	(*pipex)->out_fd = 1;
	if (argc > 1 && !ft_strncmp(argv[1], "here_doc", 8))
		(*pipex)->here_doc = 1;
	return (0);
}

int	check_args(t_pipex *pipex, int argc, char **argv)
{
	//open all needed files
	if (pipex->here_doc)
	{
	//handle here_doc (use custom gnl)

	}
	else
		pipex->in_fd = open(argv[1], O_RDONLY);
	// if not here_doc -> O_TRUNC, else -> O_APPEND
	pipex->out_fd = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (pipex->in_fd == -1 || pipex->out_fd == -1)
		return (1);
	return (0);
}

int	parse_cmds(t_pipex *pipex, int argc, char **argv, char **envp)
{
	char	*path_from_envp;
	char	**paths;
	char	**cmds;
	char	*path;
	int		exists;
	int		i;
	int		j;
	int		k;

	i = 0;
	while (ft_strncmp(*(envp + i), "PATH", 4))
		i++;
	path_from_envp = *(envp + i);
	paths = ft_split(path_from_envp, ':');

	i = 2;
	if (!ft_strncmp(argv[1], "here_doc", 8))
		i++;
	k = 0;
	cmds = ft_calloc(argc - 3, sizeof(char *));
	cmds[argc - 1] = 0;
	while (i < argc - 1)
	{
		cmds[k] = ft_split(argv[i], ' ')[0];
		exists = 0;
		if (access(cmds[k], X_OK) != -1)
			exists = 1;
		else
		{
			j = 0;
			while (paths[j])
			{
				path = paths[j];
				path = ft_strjoin(path, "/");
				path = ft_strjoin(path, cmds[k]);
				if (access(path, X_OK) != -1)
				{
					exists = 1;
					free(cmds[k]);
					cmds[k] = path;
					break;
				}
				free(path);
				j++;
			}

		}
		if (!exists)
			ft_exit(pipex, 1);
		i++;
		pipex->cmd_count++;
		k++;
	}
	pipex->cmd_count--;
	pipex->cmd_paths = cmds;
	return (0);
}

void	parse_args(t_pipex *pipex, int argc, char **argv)
{
	char	***args;
	int		i;
	int		j;

	i = 2;
	if (!ft_strncmp(argv[1], "here_doc", 8))
		i++;
	args = ft_calloc(argc - 3, sizeof(char *));
	j = 0;
	while (i < argc - 1)
	{
		args[j] = ft_split(argv[i], ' ');
		i++;
		j++;
	}
	pipex->cmd_args = args;
}

int	exec(t_pipex *pipex, int cmd_i, char **envp, int **pids, int **fds)
{
	pid_t	pid;

	if (cmd_i != pipex->cmd_count)
	{
		if (pipe(fds[cmd_i]) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		if (cmd_i == 0)
		{
			if (dup2(pipex->in_fd, 0) < 0)
				ft_exit(pipex, 1);
		}
		else
		{
			if (dup2(fds[cmd_i - 1][0], 0) < 0)
				ft_exit(pipex, 1);
		}
		if (cmd_i == pipex->cmd_count)
		{
			if (dup2(pipex->out_fd, 1) < 0)
				ft_exit(pipex, 1);
		}
		else
		{
			if (dup2(fds[cmd_i][1], 1) < 0)
				ft_exit(pipex, 1);
			close(fds[cmd_i][1]);
		}
		if (cmd_i != 0)
		{
			close(fds[cmd_i - 1][0]);
			close(fds[cmd_i - 1][1]);
		}
		if (cmd_i == 0)
			close(pipex->in_fd);
		if (cmd_i == pipex->cmd_count)
			close(pipex->out_fd);
		execve(pipex->cmd_paths[cmd_i], pipex->cmd_args[cmd_i], envp);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	else
	{
		(*pids)[cmd_i] = pid;
		ft_printf(2, "pid: %d\n", pid);
		if (cmd_i != 0)
		{
			close(fds[cmd_i - 1][0]);
			close(fds[cmd_i - 1][1]);
		}
		if (cmd_i == 0)
			close(pipex->in_fd);
		if (cmd_i == pipex->cmd_count)
			close(pipex->out_fd);
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	*pipex;

	if (init_pipex(&pipex, argc, argv))
		return (ft_exit(pipex, 1));
	if (check_args(pipex, argc, argv))
		return (ft_exit(pipex, 1));
	if (parse_cmds(pipex, argc, argv, envp))
		return (ft_exit(pipex, 1));
	parse_args(pipex, argc, argv);

	int i = 0;
	while (i <= pipex->cmd_count)
		i++;
	int	*pids;
	int	**fds;
	pids = calloc(i + 1, sizeof(int));
	fds = calloc(i, sizeof(int));
	i = 0;
	while (i <= pipex->cmd_count)
	{
		if (i < pipex->cmd_count)
			fds[i] = calloc(2, sizeof(int));
		exec(pipex, i, envp, &pids, fds);
		ft_printf(2, "iteration %d done!\n", i);
		i++;
	}
	i = 0;
	while (i <= pipex->cmd_count)
	{
		ft_printf(2, "waiting for: %d\n", pids[i]);
		if (waitpid(pids[i], 0, 0) < 0)
			ft_exit(pipex, 1);
		ft_printf(2, "%d done!\n", pids[i]);
		i++;
	}
	return (ft_exit(pipex, 0));
}
