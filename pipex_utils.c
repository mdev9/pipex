/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marde-vr <marde-vr@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:26:46 by marde-vr          #+#    #+#             */
/*   Updated: 2024/02/09 14:09:22 by marde-vr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	first_word_len(char *str)
{
	int i = 0;
	while (str[i] && !(str[i] == ' ' || str[i] == '\0'))
		i++;
	return (i);
}

int	init_pipex(t_pipex **pipex, int argc, char **argv)
{
	*pipex = ft_calloc(1, sizeof(t_pipex));
	if (!*pipex)
		return (1);
	(*pipex)->in_fd = 0;
	(*pipex)->out_fd = 1;
	if (argc > 1 && !ft_strncmp(argv[1], "here_doc", 8))
		(*pipex)->here_doc = 1;
	return (0);
}
