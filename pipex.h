/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marde-vr <marde-vr@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 16:12:57 by marde-vr          #+#    #+#             */
/*   Updated: 2024/02/09 16:43:02 by marde-vr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <stdio.h>
# include <sys/wait.h>
//# include <unistd.h>
//# include <stdlib.h>
//# include <fcntl.h>

typedef struct s_pipex
{
	int		in_fd;
	int		out_fd;
	int		here_doc;
	char	**cmd_paths;
	char	***cmd_args;
	int		*pids;
	int		**fds;
	int		cmd_count;
	char	**paths;
	char	*here_doc_file;
}				t_pipex;

int		ft_exit(t_pipex *pipex, int error);
int		first_word_len(char *str);
int		init_pipex(t_pipex **pipex, int argc, char **argv, char **envp);
int		check_args(t_pipex *pipex, int argc, char **argv);
void	parse_args(t_pipex *pipex, int argc, char **argv);
int		parse_cmds(t_pipex *pipex, int argc, char **argv);
void	pipe_child(t_pipex *pipex, int cmd_i, char **envp);
void	pipe_parent(t_pipex *pipex, int cmd_i, int pid);

#endif
