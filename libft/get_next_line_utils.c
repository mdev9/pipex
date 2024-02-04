/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marde-vr <marde-vr@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 17:45:50 by marde-vr          #+#    #+#             */
/*   Updated: 2023/12/12 13:34:51 by marde-vr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	ft_gnl_strlen(const char *s)
{
	unsigned int	i;

	i = 0;
	if (!s)
		return (i);
	while (s[i])
		i++;
	return (i);
}

void	*ft_gnl_memcpy(void *dest, const void *src, unsigned int n)
{
	unsigned int	i;
	char			*ptr_dest;
	char			*ptr_src;

	i = 0;
	ptr_dest = (char *)dest;
	ptr_src = (char *)src;
	while (i < n && ptr_dest && ptr_src)
	{
		ptr_dest[i] = ptr_src[i];
		i++;
	}
	return (ptr_dest);
}

char	*ft_gnl_strdup(const char *src)
{
	int		i;
	char	*copy;	

	i = 0;
	copy = NULL;
	while (src[i])
		i++;
	copy = malloc((i + 1) * sizeof(char));
	if (copy == NULL)
		return (NULL);
	i = 0;
	while (src[i])
	{
		copy[i] = src[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

char	*ft_gnl_strjoin(char *s1, char *s2)
{
	char			*str;
	unsigned int	s1_size;
	unsigned int	s2_size;
	unsigned int	i;

	s1_size = ft_gnl_strlen(s1);
	s2_size = ft_gnl_strlen(s2);
	str = malloc((s1_size + s2_size + 1));
	if (str == NULL)
		return (0);
	i = -1;
	while (s1 && ++i < s1_size)
		str[i] = s1[i];
	i = -1;
	while (s2 && ++i < s2_size)
		str[i + s1_size] = s2[i];
	str[i + s1_size] = 0;
	free(s1);
	return (str);
}
