/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marde-vr <marde-vr@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:26:46 by marde-vr          #+#    #+#             */
/*   Updated: 2024/02/11 20:44:31 by marde-vr         ###   ########.fr       */
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

void	get_path_from_envp(t_pipex *pipex, int argc, char **envp)
{
	char	*path_from_envp;
	char	**paths;
	char	**cmds;
	int		i;

	i = 0;
	while (ft_strncmp(*(envp + i), "PATH=", 5))
		i++;
	path_from_envp = *(envp + i);
	paths = ft_split(path_from_envp, ':');
	if (!paths)
		ft_exit(pipex, 1);
	pipex->paths = paths;
	cmds = ft_calloc(argc - 3, sizeof(char *));
	if (!cmds)
		ft_exit(pipex, 1);
	pipex->cmd_paths = cmds;
}

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

void	init_pipex(t_pipex **pipex, int argc, char **argv, char **envp)
{
	int	i;
	int	*pids;
	int	**fds;

	*pipex = ft_calloc(1, sizeof(t_pipex));
	if (!*pipex)
		ft_exit(*pipex, 1);
	(*pipex)->in_fd = 0;
	(*pipex)->out_fd = 1;
	if (argc > 1 && !ft_strncmp(argv[1], "here_doc", 8))
		(*pipex)->here_doc = 1;
	i = argc - (3 + (*pipex)->here_doc);
	pids = calloc(i + 1, sizeof(int));
	fds = calloc(i, sizeof(int *));
	(*pipex)->pids = pids;
	(*pipex)->fds = fds;
	if (!pids || !fds)
		ft_exit(*pipex, 1);
	get_path_from_envp(*pipex, argc, envp);
}
