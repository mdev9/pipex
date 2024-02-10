/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marde-vr <marde-vr@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 15:26:46 by marde-vr          #+#    #+#             */
/*   Updated: 2024/02/10 18:35:30 by marde-vr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <unistd.h>

void	redirect_input(t_pipex *pipex, int cmd_i)
{
	if (cmd_i == 0)
	{
		if (pipex->here_doc)
			pipex->in_fd = open(pipex->here_doc_file, O_RDWR, 0644);
		if (dup2(pipex->in_fd, 0) < 0)
			ft_exit(pipex, 1);
		close(pipex->in_fd);
	}
	else
	{
		if (dup2(pipex->fds[cmd_i - 1][0], 0) < 0)
			ft_exit(pipex, 1);
	}
}

void	redirect_output(t_pipex *pipex, int cmd_i)
{
	if (cmd_i == pipex->cmd_count - 1)
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
}

void	pipe_child(t_pipex *pipex, int cmd_i, char **envp)
{
	redirect_input(pipex, cmd_i);
	redirect_output(pipex, cmd_i);
	if (cmd_i != 0)
	{
		close(pipex->fds[cmd_i - 1][0]);
		close(pipex->fds[cmd_i - 1][1]);
	}
	if (cmd_i == 0 || pipex->here_doc)
		close(pipex->in_fd);
	close(pipex->fds[cmd_i][0]);
	close(pipex->fds[cmd_i][1]);
	close(pipex->out_fd);
	if (pipex->cmd_paths[cmd_i])
		execve(pipex->cmd_paths[cmd_i], pipex->cmd_args[cmd_i], envp);
	close(0);
	close(1);
	close(2);
	perror("execve");
	ft_exit(pipex, 1);
}

void	pipe_parent(t_pipex *pipex, int cmd_i, int pid)
{
	pipex->pids[cmd_i] = pid;
	if (cmd_i != 0)
	{
		close(pipex->fds[cmd_i - 1][0]);
		close(pipex->fds[cmd_i - 1][1]);
	}
	if (cmd_i == 0)
		close(pipex->in_fd);
	if (cmd_i == pipex->cmd_count - 1)
	{
		close(pipex->fds[cmd_i][0]);
		close(pipex->fds[cmd_i][1]);
		close(pipex->out_fd);
	}
}
