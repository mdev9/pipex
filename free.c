/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marde-vr <marde-vr@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 14:00:12 by marde-vr          #+#    #+#             */
/*   Updated: 2024/02/09 14:07:43 by marde-vr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_cmd_args(t_pipex *pipex)
{
	int i;

	i = 0;
	while (i <= pipex->cmd_count)
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
	free(pipex->cmd_args);
}

void	free_paths(t_pipex *pipex)
{
	int i;

	if (pipex->cmd_paths)
	{
		i = 0;
		while (i <= pipex->cmd_count)
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
	int i;

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
}

int ft_exit(t_pipex *pipex, int error)
{
	// - potentially remove the temporary here_doc file using unlink
	
	int i;
	if (pipex)
	{
		free_struct(pipex);
		free(pipex);
	}
	exit(error);
	return (error);
}
