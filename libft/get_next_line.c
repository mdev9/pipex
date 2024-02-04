/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marde-vr <marde-vr@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 17:42:53 by marde-vr          #+#    #+#             */
/*   Updated: 2023/12/12 13:35:12 by marde-vr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_stash_to_line(char *stash)
{
	char	*line;
	int		i;

	i = 0;
	if (!stash)
		return (NULL);
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\n')
		i++;
	line = malloc(i + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (stash[i])
	{
		line[i] = stash[i];
		i++;
		if (stash[i - 1] == '\n')
			break ;
	}
	line[i] = '\0';
	return (line);
}

char	*ft_rm_line_from_stash(char *stash)
{
	char	*res;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!stash)
		return (NULL);
	while (stash[i])
		i++;
	res = malloc(i + 1);
	if (!res)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\n')
		i++;
	while (stash[i])
		res[j++] = stash[i++];
	res[j] = '\0';
	free(stash);
	return (res);
}

int	nl_is_in_stash(char *stash)
{
	int	i;

	i = 0;
	if (!stash)
		return (1);
	while (stash[i])
	{
		if (stash[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_return_next_line(char **stash, char *buffer)
{
	char	*line;

	line = ft_stash_to_line(*stash);
	*stash = ft_rm_line_from_stash(*stash);
	free(buffer);
	if (!**stash)
	{
		free(*stash);
		*stash = NULL;
	}
	if (!*line)
	{
		free(line);
		return (0);
	}
	return (line);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	int			nb_read;
	static char	*stash;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	if (!stash)
		stash = ft_gnl_strdup("");
	nb_read = BUFFER_SIZE;
	while (1)
	{
		if (!nl_is_in_stash(stash))
			nb_read = read(fd, buffer, BUFFER_SIZE);
		if (nb_read == -1 || nb_read == 0 || nl_is_in_stash(stash))
			return (ft_return_next_line(&stash, buffer));
		buffer[nb_read] = '\0';
		stash = ft_gnl_strjoin(stash, buffer);
	}
}
