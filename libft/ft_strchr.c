/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marde-vr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 14:46:57 by marde-vr          #+#    #+#             */
/*   Updated: 2023/11/05 01:45:19 by marde-vr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	int		len;
	char	*ptr;

	i = 0;
	ptr = (char *)s;
	len = ft_strlen(ptr);
	while (i <= len)
	{
		if (ptr[i] == (char)c)
			return (ptr + i);
		i++;
	}
	return (0);
}
