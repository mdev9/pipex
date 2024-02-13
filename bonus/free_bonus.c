/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marde-vr <marde-vr@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 14:00:12 by marde-vr          #+#    #+#             */
/*   Updated: 2024/02/13 14:55:46 by marde-vr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include <unistd.h>

void	free_cmd_args(t_pipex *pipex)
{
	int	i;
	int	j;

	i = 0;
	while (i < pipex->cmd_count)
	{
		j = 0;
		while (pipex->cmd_args[i][j])
		{
			free(pipex->cmd_args[i][j]);
			j++;
		}
		free(pipex->cmd_args[i]);
		i++;
	}
	free(pipex->cmd_args);
}

void	free_paths(t_pipex *pipex)
{
	int	i;

	if (pipex->cmd_paths)
	{
		i = 0;
		while (pipex->cmd_count && i < pipex->cmd_count)
		{
			free(pipex->cmd_paths[i]);
			i++;
		}
		free(pipex->cmd_paths);
	}
	if (pipex->paths)
	{
		i = 0;
		while (pipex->paths[i])
		{
			free(pipex->paths[i]);
			i++;
		}
		free(pipex->paths);
	}
}

void	free_struct(t_pipex *pipex)
{
	int	i;

	free_paths(pipex);
	if (pipex->cmd_args)
		free_cmd_args(pipex);
	if (pipex->pids)
		free(pipex->pids);
	if (pipex->fds)
	{
		i = 0;
		while (i < pipex->cmd_count)
		{
			free(pipex->fds[i]);
			i++;
		}
		free(pipex->fds);
	}
	if (pipex->here_doc_file)
	{
		unlink(pipex->here_doc_file);
		free(pipex->here_doc_file);
	}
}

int	ft_exit(t_pipex *pipex, int error)
{
	if (error == 1)
		ft_printf(2, "pipex: error\n");
	else if (error == 2)
		perror("open");
	if (pipex->in_fd != -1)
		close(pipex->in_fd);
	if (pipex->out_fd != -1)
		close(pipex->out_fd);
	close(0);
	close(1);
	close(2);
	if (pipex)
	{
		free_struct(pipex);
		free(pipex);
	}
	exit(error);
	return (error);
}
