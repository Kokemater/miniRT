/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoraled <dmoraled@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:54:16 by dmoraled          #+#    #+#             */
/*   Updated: 2024/12/02 16:42:14 by dmoraled         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

int	print_hex_lower(unsigned long long num)
{
	int	d;
	int	len;

	if (num == 0)
	{
		ft_putchar_fd('0', 1);
		return (1);
	}
	len = 0;
	if (num >= 16)
		len += print_hex_lower(num / 16);
	d = num % 16;
	if (d > 9)
		ft_putchar_fd((d - 10) + 'a', 1);
	else
		ft_putchar_fd(d + '0', 1);
	++len;
	return (len);
}

int	print_hex_upper(unsigned long long num)
{
	int	d;
	int	len;

	if (num == 0)
	{
		ft_putchar_fd('0', 1);
		return (1);
	}
	len = 0;
	if (num >= 16)
		len += print_hex_upper(num / 16);
	d = num % 16;
	if (d > 9)
		ft_putchar_fd((d - 10) + 'A', 1);
	else
		ft_putchar_fd(d + '0', 1);
	++len;
	return (len);
}

int	print_ptr(void *ptr)
{
	if (!ptr)
	{
		ft_putstr_fd("(nil)", 1);
		return (5);
	}
	ft_putstr_fd("0x", 1);
	return (2 + print_hex_lower((unsigned long long)ptr));
}
