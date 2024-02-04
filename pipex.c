/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marde-vr <marde-vr@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 20:26:11 by marde-vr          #+#    #+#             */
/*   Updated: 2024/02/04 16:57:59 by marde-vr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	init_pipex(t_pipex **pipex)
{
	pipex = ft_calloc(1, t_pipex);
	if (!*pipex)
		return (1);

	// init struct;

	return (0);
}

int	check_args(int argc, char **argv)
{
	//open all needed files
	//handle here_doc (use custom gnl)
}

int parse_cmds(t_pipex *pipex, int argc, char **argv)
{
	// create command arrray: ["/bin/cat", "/usr/bin/head", "/usr/bin/wc"]
	// null terminate the arrays
	// store result in pipex struct;
}

int	parse_args(t_pipex *pipex, int argc, char **argv)
{
	// ft_split args: [["cat"], ["head", "-n", "5"], ["wc", "-l"]]
	// null terminate the arrays
	// store result in pipex struct;
}

int	exec()
{
	int	fd[2];
	pid_t pid;

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

int	ft_error()

int	ft_exit(t_pipex *pipex, int error_code)
{
	// called when done done executing or if a malloc failed
	// clean struct:
	// - close all FDs
	// - free all allocated memory
	// - potentially remove the temporary here_doc file using unlink
}

int	main(int argc, char **argv)
{
	t_pipex *pipex;

	if (init_pipex(&pipex))
		return (ft_exit(pipex, 1));
	if (check_args())
		return (ft_exit(pipex, 1));
	if (parse_cmds())
		return (ft_exit(pipex, 1));
	if (parse_args())
		return (ft_exit(pipex, 1));
	while(cmds)
		exec();
	return(ft_exit(pipex, 0));
}
