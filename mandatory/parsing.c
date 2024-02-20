/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marde-vr <marde-vr@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 14:10:06 by marde-vr          #+#    #+#             */
/*   Updated: 2024/02/20 13:27:29 by marde-vr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	check_args(t_pipex *pipex, int argc, char **argv)
{
	if (argc > 5)
	{
		ft_printf(2, "pipex: error: too many arguments\n");
		ft_exit(pipex, 0);
	}
	pipex->in_fd = open(argv[1], O_RDONLY);
	pipex->out_fd = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (pipex->in_fd == -1)
	{
		perror("open");
	}
	if (pipex->out_fd == -1)
		ft_exit(pipex, 2);
}

void	find_cmd_path(t_pipex *pipex, int cmd, int *exists)
{
	char	*tmp;
	char	*path;
	int		i;

	i = 0;
	while (pipex->paths[i])
	{
		path = pipex->paths[i];
		tmp = ft_strjoin(path, "/");
		if (!tmp)
			ft_exit(pipex, 1);
		path = ft_strjoin(tmp, pipex->cmd_paths[cmd]);
		if (!path)
			ft_exit(pipex, 1);
		free(tmp);
		if (access(path, X_OK) != -1)
		{
			*exists = 1;
			free(pipex->cmd_paths[cmd]);
			pipex->cmd_paths[cmd] = path;
			break ;
		}
		free(path);
		i++;
	}
}

void	parse_cmds(t_pipex *pipex, int argc, char **argv)
{
	int	exists;
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (++i < argc - 1)
	{
		pipex->cmd_paths[j] = ft_substr(argv[i], 0, first_word_len(argv[i]));
		if (!pipex->cmd_paths[j])
			ft_exit(pipex, 1);
		exists = 0;
		if (access(pipex->cmd_paths[j], X_OK) != -1)
			exists = 1;
		else
			find_cmd_path(pipex, j, &exists);
		if (!exists)
		{
			ft_printf(2, "%s: command not found\n", pipex->cmd_paths[j]);
			free(pipex->cmd_paths[j]);
			pipex->cmd_paths[j] = 0;
		}
		j++;
		pipex->cmd_count++;
	}
}

void	parse_args(t_pipex *pipex, int argc, char **argv)
{
	char	***args;
	int		i;
	int		j;

	i = 2;
	args = ft_calloc(argc - 3, sizeof(char *));
	if (!args)
		ft_exit(pipex, 1);
	j = 0;
	while (i < argc - 1)
	{
		args[j] = ft_split(argv[i], ' ');
		if (!args[j])
			ft_exit(pipex, 1);
		i++;
		j++;
	}
	pipex->cmd_args = args;
}
