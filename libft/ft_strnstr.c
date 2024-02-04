/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marde-vr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 11:07:02 by marde-vr          #+#    #+#             */
/*   Updated: 2023/11/03 20:44:32 by marde-vr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	k;
	char			*ptr;

	i = 0;
	ptr = (char *)big;
	if (little && *little == 0)
		return (ptr);
	while (i <= len && little && big && big[i])
	{
		if (big[i] == little[0])
		{
			k = i;
			j = 0;
			while (i < len && big[i++] == little[j++])
			{
				if (little[j] == '\0')
					return (ptr + k);
			}
			i = k;
		}
		i++;
	}
	return (0);
}
