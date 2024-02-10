/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marde-vr <marde-vr@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 14:10:06 by marde-vr          #+#    #+#             */
/*   Updated: 2024/02/10 18:28:02 by marde-vr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	handle_here_doc(t_pipex *pipex, int argc, char **argv)
{
	char	*line;
	char	*eof;

	pipex->here_doc_file = get_tmp_file_name(argc, argv);
	pipex->in_fd = open(pipex->here_doc_file, O_CREAT | O_RDWR, 0644);
	ft_printf(2, "here_doc> ");
	line = get_next_line(0);
	write(pipex->in_fd, line, ft_strlen(line));
	eof = ft_strjoin(argv[2], "\n");
	while (ft_strncmp(line, eof, (ft_strlen(argv[2]) + 1)))
	{
		ft_printf(2, "here_doc> ");
		free(line);
		line = get_next_line(0);
		if (ft_strncmp(line, eof, (ft_strlen(argv[2]) + 1)))
			write(pipex->in_fd, line, ft_strlen(line));
	}
	free(eof);
	free(line);
	pipex->out_fd = open(argv[argc - 1], O_CREAT | O_RDWR | O_APPEND, 0644);
	close(pipex->in_fd);
}

int	check_args(t_pipex *pipex, int argc, char **argv)
{
	if (argc < (5 + pipex->here_doc))
		ft_exit(pipex, 0);
	if (pipex->here_doc)
		handle_here_doc(pipex, argc, argv);
	else
	{
		pipex->in_fd = open(argv[1], O_RDONLY);
		pipex->out_fd = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	}
	if (pipex->in_fd == -1 || pipex->out_fd == -1)
		return (1);
	return (0);
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
		path = ft_strjoin(tmp, pipex->cmd_paths[cmd]);
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

int	parse_cmds(t_pipex *pipex, int argc, char **argv)
{
	int	exists;
	int	i;
	int	j;

	i = 1;
	if (!ft_strncmp(argv[1], "here_doc", 8))
		i++;
	j = 0;
	while (++i < argc - 1)
	{
		pipex->cmd_paths[j] = ft_substr(argv[i], 0, first_word_len(argv[i]));
		exists = 0;
		if (access(pipex->cmd_paths[j], X_OK) != -1)
			exists = 1;
		else
			find_cmd_path(pipex, j, &exists);
		if (!exists)
		{
			free(pipex->cmd_paths[j]);
			pipex->cmd_paths[j] = 0;
		}
		j++;
		pipex->cmd_count++;
	}
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
