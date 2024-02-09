/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marde-vr <marde-vr@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 20:26:11 by marde-vr          #+#    #+#             */
/*   Updated: 2024/02/09 14:20:00 by marde-vr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	exec(t_pipex *pipex, int cmd_i, char **envp)
{
	pid_t	pid;

	if (cmd_i != pipex->cmd_count)
	{
		if (pipe(pipex->fds[cmd_i]) == -1)
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
			if (dup2(pipex->fds[cmd_i - 1][0], 0) < 0)
				ft_exit(pipex, 1);
		}
		if (cmd_i == pipex->cmd_count)
		{
			if (dup2(pipex->out_fd, 1) < 0)
				ft_exit(pipex, 1);
		}
		else
		{
			if (dup2(pipex->fds[cmd_i][1], 1) < 0)
				ft_exit(pipex, 1);
			close(pipex->fds[cmd_i][1]);
		}
		if (cmd_i != 0)
		{
			close(pipex->fds[cmd_i - 1][0]);
			close(pipex->fds[cmd_i - 1][1]);
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
		pipex->pids[cmd_i] = pid;
		ft_printf(2, "pid: %d\n", pid);
		if (cmd_i != 0)
		{
			close(pipex->fds[cmd_i - 1][0]);
			close(pipex->fds[cmd_i - 1][1]);
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
	fds = calloc(i, sizeof(int *));
	pipex->pids = pids;
	pipex->fds = fds;
	if (! pids || !fds)
		ft_exit(pipex, 1);
	i = 0;
	while (i <= pipex->cmd_count)
	{
		if (i < pipex->cmd_count)
			pipex->fds[i] = calloc(2, sizeof(int));
		if (pipex->cmd_paths)
			exec(pipex, i, envp);
		i++;
	}
	i = 0;
	waitpid(pipex->pids[pipex->cmd_count], 0, 0);
	//while (i <= pipex->cmd_count)
	//{
	//	if (waitpid(pipex->pids[i], 0, 0) < 0)
	//		ft_exit(pipex, 1);
	//	i++;
	//}
	return (ft_exit(pipex, 0));
}
