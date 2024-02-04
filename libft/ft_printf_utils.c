/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marde-vr <marde-vr@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 21:06:24 by marde-vr          #+#    #+#             */
/*   Updated: 2024/01/17 15:23:57 by marde-vr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstr(const char *s)
{
	int	i;

	i = 0;
	if (!s)
	{
		write(1, &"(null)", 6);
		return (6);
	}
	while (s[i])
	{
		write(1, &s[i], 1);
		i++;
	}
	return (i);
}

int	ft_putnbr(long nb)
{
	int	n;

	n = 0;
	if (nb < 0)
	{
		write(1, "-", 1);
		nb = nb * -1;
		n++;
	}
	if (nb > 9)
	{
		n += ft_putnbr(nb / 10);
	}
	write(1, &(char){nb % 10 + 48}, 1);
	return (n + 1);
}

int	ft_putptr(long unsigned int ptr)
{
	int	n;

	if (!ptr)
	{
		write(1, &"(nil)", 5);
		return (5);
	}
	ft_putstr("0x");
	n = 2;
	n += ft_puthexa_ptr(ptr);
	return (n);
}

int	ft_puthexa(unsigned int nbr, char c)
{
	int	n;

	n = 0;
	if (nbr > 15)
		n += ft_puthexa(nbr / 16, c);
	if (c == 'X')
		write(1, &"0123456789ABCDEF"[nbr % 16], 1);
	if (c == 'x')
		write(1, &"0123456789abcdef"[nbr % 16], 1);
	return (n + 1);
}

int	ft_puthexa_ptr(unsigned long nbr)
{
	int	n;

	n = 0;
	if (nbr > 15)
		n += ft_puthexa_ptr(nbr / 16);
	write(1, &"0123456789abcdef"[nbr % 16], 1);
	return (n + 1);
}
