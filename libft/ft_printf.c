/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marde-vr <marde-vr@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 20:51:52 by marde-vr          #+#    #+#             */
/*   Updated: 2023/12/12 13:39:05 by marde-vr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_print_arg(va_list args_lst, char c)
{
	int	n;

	n = 0;
	if (c == 'c')
		n += ft_putchar(va_arg(args_lst, int));
	else if (c == 's')
		n += ft_putstr(va_arg(args_lst, char *));
	else if (c == 'p')
		n += ft_putptr(va_arg(args_lst, long unsigned int));
	else if (c == 'd' || c == 'i')
		n += ft_putnbr(va_arg(args_lst, int));
	else if (c == 'u')
		n += ft_putnbr(va_arg(args_lst, unsigned int));
	else if (c == 'x' || c == 'X')
		n += ft_puthexa(va_arg(args_lst, unsigned int), c);
	else if (c == '\0')
		return (-1);
	else
	{
		n += ft_putchar('%');
	}
	return (n);
}

int	ft_conversion_is_handled(char c)
{
	if ((c == 'c' || c == 's' || c == 'p' || c == 'd' || c == 'i'
			|| c == 'u' || c == 'x' || c == 'X' || c == '%'))
		return (1);
	return (0);
}

int	ft_printf(const char *s, ...)
{
	int		n;
	int		i;
	va_list	args_lst;

	n = 0;
	i = 0;
	va_start(args_lst, s);
	while (s[i])
	{
		if (s[i] == '%' && ft_conversion_is_handled(s[i + 1]))
		{
			n += ft_print_arg(args_lst, s[i + 1]);
			if (s[i + 1] != '\0')
				i += 2;
			else
				i++;
		}
		else
		{
			n += ft_putchar(s[i]);
			i++;
		}
	}
	va_end(args_lst);
	return (n);
}
