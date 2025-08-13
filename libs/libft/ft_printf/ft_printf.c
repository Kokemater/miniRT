/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoraled <dmoraled@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:53:51 by dmoraled          #+#    #+#             */
/*   Updated: 2024/12/02 16:41:41 by dmoraled         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdarg.h>

#include "../libft.h"
#include "ft_printf.h"

static int	print_arg(const char c, va_list args)
{
	if (!c)
		return (0);
	if (c == 'c')
		return (print_char(va_arg(args, int)));
	if (c == 's')
		return (print_str(va_arg(args, char *)));
	if (c == 'd' || c == 'i')
		return (print_num(va_arg(args, int)));
	if (c == 'u')
		return (print_unum(va_arg(args, unsigned int)));
	if (c == 'x')
		return (print_hex_lower(va_arg(args, unsigned int)));
	if (c == 'X')
		return (print_hex_upper(va_arg(args, unsigned int)));
	if (c == 'p')
		return (print_ptr(va_arg(args, void *)));
	ft_putchar_fd('%', 1);
	if (c != '%')
	{
		ft_putchar_fd(c, 1);
		return (2);
	}
	return (1);
}

int	ft_printf(const char *fmt, ...)
{
	int		len;
	va_list	args;

	va_start(args, fmt);
	len = 0;
	while (*fmt)
	{
		if (*fmt == '%')
		{
			len += print_arg(*(fmt + 1), args);
			++fmt;
		}
		else
		{
			write(1, fmt, 1);
			++len;
		}
		++fmt;
	}
	va_end(args);
	return (len);
}
