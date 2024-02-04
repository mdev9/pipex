/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marde-vr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 14:15:12 by marde-vr          #+#    #+#             */
/*   Updated: 2023/11/05 02:22:00 by marde-vr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	ft_nword(char const *s, char c)
{
	int	nword;
	int	i;
	int	previous_is_c;

	nword = 0;
	previous_is_c = 0;
	i = 0;
	while (s[i] == c && s[i])
		i++;
	if (!s[i])
		return (nword);
	while (s[i])
	{
		if (s[i] == c && !previous_is_c)
			nword++;
		if (s[i] == c)
			previous_is_c = 1;
		if (s[i] != c)
			previous_is_c = 0;
		i++;
	}
	if (s[i - 1] == c)
		nword--;
	return (nword + 1);
}

static char	*ft_strndup(const char *src, size_t n)
{
	unsigned int	i;
	char			*copy;	

	i = 0;
	copy = NULL;
	while (src[i])
		i++;
	if (i > n)
		i = n;
	copy = malloc((i + 1) * sizeof(char));
	if (copy == NULL)
		return (NULL);
	i = 0;
	while (src[i] && i < n)
	{
		copy[i] = src[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

static void	ft_free_array(char **str_array, int n)
{
	int	i;

	i = 0;
	if (!str_array)
	{
		while (i < n)
		{
			free(str_array[i]);
			i++;
		}
		free(str_array);
	}
}

static void	ft_fill_array(char const *s, char c, char **str_array)
{
	int		i;
	int		j;
	int		word_start;

	i = 0;
	j = 0;
	word_start = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		word_start = i;
		while (s[i] != c && s[i])
			i++;
		if (!s[i] && s[i - 1] == c)
			break ;
		str_array[j] = ft_strndup(s + word_start, i - word_start);
		if (!str_array[j])
			ft_free_array(str_array, j);
		j++;
	}
	str_array[j] = 0;
}

char	**ft_split(char const *s, char c)
{
	char	**str_array;

	if (!s)
		return (NULL);
	str_array = malloc(sizeof(char *) * (ft_nword(s, c) + 1));
	if (!str_array)
		return (NULL);
	ft_fill_array(s, c, str_array);
	return (str_array);
}
