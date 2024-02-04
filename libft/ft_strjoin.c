/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marde-vr <marde-vr@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 20:23:21 by marde-vr          #+#    #+#             */
/*   Updated: 2023/11/01 21:21:02 by marde-vr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*str;
	unsigned int	s1_size;
	unsigned int	s2_size;
	unsigned int	i;

	if (!s1 || !s2)
	{
		str = malloc(sizeof(char));
		*str = 0;
		return (str);
	}
	s1_size = ft_strlen(s1);
	s2_size = ft_strlen(s2);
	str = malloc((s1_size + s2_size + 1));
	if (str == NULL)
		return (0);
	i = -1;
	while (++i < s1_size)
		str[i] = s1[i];
	i = -1;
	while (++i < s2_size)
		str[i + s1_size] = s2[i];
	str[i + s1_size] = 0;
	return (str);
}
