/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_num.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoraled <dmoraled@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:54:19 by dmoraled          #+#    #+#             */
/*   Updated: 2024/12/02 16:42:20 by dmoraled         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

static int	count_num_digits(int num)
{
	int	len;

	if (num == -2147483648)
		return (11);
	len = 0;
	if (num < 0)
	{
		len++;
		num = -num;
	}
	if (num == 0)
		return (1);
	while (num > 0)
	{
		len++;
		num /= 10;
	}
	return (len);
}

static int	count_unum_digits(unsigned int num)
{
	int	len;

	len = 0;
	if (num == 0)
		return (1);
	while (num > 0)
	{
		len++;
		num /= 10;
	}
	return (len);
}

int	print_unum(unsigned int num)
{
	ft_putunbr_fd(num, 1);
	return (count_unum_digits(num));
}

int	print_num(int num)
{
	ft_putnbr_fd(num, 1);
	return (count_num_digits(num));
}
