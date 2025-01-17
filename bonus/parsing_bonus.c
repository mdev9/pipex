/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marde-vr <marde-vr@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 14:10:06 by marde-vr          #+#    #+#             */
/*   Updated: 2024/02/15 16:45:30 by marde-vr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	check_args(t_pipex *pipex, int argc, char **argv)
{
	if (pipex->here_doc)
		handle_here_doc(pipex, argc, argv);
	else
	{
		pipex->in_fd = open(argv[1], O_RDONLY);
		pipex->out_fd = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	}
	if (pipex->in_fd == -1)
		perror("open");
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

void	check_if_command_exists(t_pipex *pipex, int i)
{
	int	exists;

	exists = 0;
	if (access(pipex->cmd_paths[i], X_OK) != -1)
		exists = 1;
	else
		find_cmd_path(pipex, i, &exists);
	if (!exists)
	{
		ft_printf(2, "%s: command not found\n", pipex->cmd_paths[i]);
		free(pipex->cmd_paths[i]);
		pipex->cmd_paths[i] = 0;
	}
}

void	parse_cmds(t_pipex *pipex, int argc, char **argv)
{
	int	i;
	int	j;

	i = 2;
	if (!ft_strncmp(argv[1], "here_doc", 8))
		i++;
	j = 0;
	while (i < argc - 1)
	{
		pipex->cmd_paths[j] = ft_substr(argv[i], 0, first_word_len(argv[i]));
		if (!pipex->cmd_paths[j])
			ft_exit(pipex, 1);
		check_if_command_exists(pipex, j);
		i++;
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
	if (!ft_strncmp(argv[1], "here_doc", 8))
		i++;
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
