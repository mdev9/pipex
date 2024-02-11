/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marde-vr <marde-vr@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 21:33:07 by marde-vr          #+#    #+#             */
/*   Updated: 2024/02/11 22:05:59 by marde-vr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*get_tmp_file_name(t_pipex *pipex, int argc, char **argv)
{
	int		i;
	char	*tmp_file_name;
	char	*res;
	char	*i_char;

	i = 0;
	tmp_file_name = ".tmp";
	i_char = ft_itoa(i);
	res = ft_strjoin(tmp_file_name, i_char);
	if (!res)
		ft_exit(pipex, 1);
	free(i_char);
	while (!ft_strncmp(res, argv[argc - 1], ft_strlen(res))
		|| !access(res, F_OK))
	{
		free(res);
		i_char = ft_itoa(i);
		res = ft_strjoin(tmp_file_name, i_char);
		if (!res)
			ft_exit(pipex, 1);
		free(i_char);
		i++;
	}
	return (res);
}

void	get_here_doc_input(t_pipex *pipex, char **argv, char *eof)
{
	char	*line;

	line = NULL;
	while (!line || ft_strncmp(line, eof, ft_strlen(argv[2]) + 1))
	{
		ft_printf(1, "> ");
		free(line);
		line = get_next_line(0);
		if (!line)
		{
			ft_printf(2, "\npipex: here-document delimited by end-of-file\n");
			break ;
		}
		if (ft_strncmp(line, eof, (ft_strlen(argv[2]) + 1)))
			write(pipex->in_fd, line, ft_strlen(line));
	}
	free(eof);
	free(line);
}

void	handle_here_doc(t_pipex *pipex, int argc, char **argv)
{
	char	*eof;

	pipex->here_doc_file = get_tmp_file_name(pipex, argc, argv);
	pipex->in_fd = open(pipex->here_doc_file, O_CREAT | O_RDWR, 0644);
	if (pipex->in_fd == -1)
		ft_exit(pipex, 2);
	eof = ft_strjoin(argv[2], "\n");
	if (!eof)
		ft_exit(pipex, 1);
	get_here_doc_input(pipex, argv, eof);
	pipex->out_fd = open(argv[argc - 1], O_CREAT | O_RDWR | O_APPEND, 0644);
	if (pipex->out_fd == -1)
		ft_exit(pipex, 2);
}
