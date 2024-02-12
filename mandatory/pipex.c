/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marde-vr <marde-vr@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 20:26:11 by marde-vr          #+#    #+#             */
/*   Updated: 2024/02/12 17:50:11 by marde-vr         ###   ########.fr       */
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
			ft_exit(pipex, 1);
		}
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		ft_exit(pipex, 1);
	}
	if (pid == 0)
		pipe_child(pipex, cmd_i, envp);
	else
		pipe_parent(pipex, cmd_i, pid);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	*pipex;
	int		i;

	init_pipex(&pipex, argc, envp);
	check_args(pipex, argc, argv);
	parse_cmds(pipex, argc, argv);
	parse_args(pipex, argc, argv);
	i = 0;
	while (i < pipex->cmd_count)
	{
		pipex->fds[i] = ft_calloc(2, sizeof(int));
		if (!pipex->fds[i])
			ft_exit(pipex, 1);
		exec(pipex, i, envp);
		i++;
	}
	i = pipex->cmd_count - 1;
	while (i >= 0)
	{
		if (waitpid(pipex->pids[i], 0, 0) < 0)
			ft_exit(pipex, 1);
		i--;
	}
	return (ft_exit(pipex, 0));
}
