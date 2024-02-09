/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marde-vr <marde-vr@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 14:10:06 by marde-vr          #+#    #+#             */
/*   Updated: 2024/02/09 14:36:00 by marde-vr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	check_args(t_pipex *pipex, int argc, char **argv)
{
	if (argc < 5)
		ft_exit(pipex, 0);
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
	char	*tmp;
	int		exists;
	int		i;
	int		j;
	int		k;

	i = 0;
	while (ft_strncmp(*(envp + i), "PATH=", 5))
		i++;
	path_from_envp = *(envp + i);
	paths = ft_split(path_from_envp, ':');
	pipex->paths = paths;
	i = 2;
	if (!ft_strncmp(argv[1], "here_doc", 8))
		i++;
	k = 0;
	cmds = ft_calloc(argc - 3, sizeof(char *));
	if (!cmds)
	{
		pipex->cmd_paths = cmds;
		ft_exit(pipex, 1);
	}
	while (i < argc - 1)
	{
		cmds[k] = ft_substr(argv[i], 0, first_word_len(argv[i]));
		exists = 0;
		if (access(cmds[k], X_OK) != -1)
			exists = 1;
		else
		{
			j = 0;
			while (paths[j])
			{
				path = paths[j];
				tmp = ft_strjoin(path, "/");
				path = ft_strjoin(tmp, cmds[k]);
				free(tmp);
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
		{
			free(cmds[k]);
			cmds[k] = 0;
		}
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
	if (!args)
		ft_exit(pipex, 1);
	j = 0;
	while (i < argc - 1)
	{
		args[j] = ft_split(argv[i], ' ');
		i++;
		j++;
	}
	pipex->cmd_args = args;
}
