/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marde-vr <marde-vr@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 16:12:57 by marde-vr          #+#    #+#             */
/*   Updated: 2024/02/11 21:59:30 by marde-vr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <sys/wait.h>
# include <stdio.h>

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
void	init_pipex(t_pipex **pipex, int argc, char **argv, char **envp);
void	check_args(t_pipex *pipex, int argc, char **argv);
void	parse_args(t_pipex *pipex, int argc, char **argv);
void	parse_cmds(t_pipex *pipex, int argc, char **argv);
void	pipe_child(t_pipex *pipex, int cmd_i, char **envp);
void	pipe_parent(t_pipex *pipex, int cmd_i, int pid);
char	*get_tmp_file_name(t_pipex *pipex, int argc, char **argv);
void	handle_here_doc(t_pipex *pipex, int argc, char **argv);

#endif
