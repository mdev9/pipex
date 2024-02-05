/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marde-vr <marde-vr@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 20:26:11 by marde-vr          #+#    #+#             */
/*   Updated: 2024/02/05 15:30:07 by marde-vr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	init_pipex(t_pipex **pipex)
{
	*pipex = ft_calloc(1, sizeof(t_pipex));
	if (!*pipex)
		return (1);
	// init struct;
	return (0);
}

int	check_args(t_pipex *pipex, int argc, char **argv)
{
	//open all needed files
	//handle here_doc (use custom gnl)
	(void)pipex;
	(void)argc;
	(void)argv;
	return (0);
}

int	parse_cmds(t_pipex *pipex, int argc, char **argv, char **envp)
{
	// create command arrray: ["/bin/cat", "/usr/bin/head", "/usr/bin/wc"]
	// null terminate the arrays
	// store result in pipex struct;
	char	**cmds;
	int		i;

	i = 2;
	if (ft_strncmp(argv[1], "here_doc", 8))
		i++;
	cmds = ft_calloc(argc - 3, sizeof(char *));
	while (i < argc - 1)
	{
		cmds[i] = ft_split(argv[i], ' ')[0];
		(void)envp;
		i++;
	}
	pipex->cmd_paths = cmds;
	return (0);
}

void	parse_args(t_pipex *pipex, int argc, char **argv)
{
	// ft_split args: [["cat"], ["head", "-n", "5"], ["wc", "-l"]]
	// null terminate the arrays
	// store result in pipex struct;
	char	***args;
	int		i;

	i = 2;
	if (ft_strncmp(argv[1], "here_doc", 8))
		i++;
	args = ft_calloc(argc - 3, sizeof(char *));
	while (i < argc - 1)
	{
		args[i] = ft_split(argv[i], ' ');
		i++;
	}
	pipex->cmd_args = args;
}

/*
int	exec(void)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		dup2();
		execve();
	}
	else
	{
		dup2();
		waitpid();
	}
}

int	ft_error(void)
*/

int ft_exit(t_pipex *pipex, int error_code)
{
	(void)pipex;
	(void)error_code;
	// called when done done executing or if a malloc failed
	// clean struct:
	// - close all FDs
	// - free all allocated memory
	// - potentially remove the temporary here_doc file using unlink
	
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	*pipex;

	if (init_pipex(&pipex))
		return (ft_exit(pipex, 1));
	if (check_args(pipex, argc, argv))
		return (ft_exit(pipex, 1));
	if (parse_cmds(pipex, argc, argv, envp))
		return (ft_exit(pipex, 1));
	parse_args(pipex, argc, argv);
	//while (cmds)
	//	exec();
	return (ft_exit(pipex, 0));
}
