/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marde-vr <marde-vr@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:26:46 by marde-vr          #+#    #+#             */
/*   Updated: 2024/02/13 12:47:57 by marde-vr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	first_word_len(char *str)
{
	int	i;

	i = 0;
	while (str[i] && !(str[i] == ' ' || str[i] == '\0'))
		i++;
	return (i);
}

void	split_paths(t_pipex *pipex, char *path_from_envp)
{
	char	**paths;

	paths = ft_split(path_from_envp, ':');
	if (!paths)
		ft_exit(pipex, 1);
	pipex->paths = paths;
}

void	get_path_from_envp(t_pipex *pipex, int argc, char **envp)
{
	int		path_in_envp;
	char	**cmds;
	int		i;

	i = 0;
	path_in_envp = 0;
	while (envp[i])
	{
		if (!ft_strncmp(*(envp + i), "PATH=", 5))
		{
			path_in_envp = 1;
			break ;
		}
		i++;
	}
	if (!path_in_envp)
	{
		ft_printf(2, "pipex: error: PATH not found\n");
		ft_exit(pipex, 0);
	}
	split_paths(pipex, *(envp + i));
	cmds = ft_calloc(argc - 3, sizeof(char *));
	if (!cmds)
		ft_exit(pipex, 1);
	pipex->cmd_paths = cmds;
}

void	init_pipex(t_pipex **pipex, int argc, char **envp)
{
	int	i;
	int	*pids;
	int	**fds;

	*pipex = ft_calloc(1, sizeof(t_pipex));
	if (!*pipex)
		ft_exit(*pipex, 1);
	(*pipex)->in_fd = 0;
	(*pipex)->out_fd = 1;
	if (argc < 5)
	{
		ft_printf(2, "pipex: error: not enough arguments\n");
		ft_exit(*pipex, 0);
	}
	i = argc - 3;
	pids = ft_calloc(i + 1, sizeof(int));
	fds = ft_calloc(i, sizeof(int *));
	(*pipex)->pids = pids;
	(*pipex)->fds = fds;
	if (!pids || !fds)
		ft_exit(*pipex, 1);
	get_path_from_envp(*pipex, argc, envp);
}
