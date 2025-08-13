/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoraled <dmoraled@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 17:25:01 by dmoraled          #+#    #+#             */
/*   Updated: 2024/10/09 18:29:06 by dmoraled         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	num_len(int n)
{
	int	ret;

	ret = 0;
	if (n < 0)
		++ret;
	else if (n == 0)
		return (1);
	while (n != 0)
	{
		n /= 10;
		++ret;
	}
	return (ret);
}

char	*ft_itoa(int n)
{
	int		len;
	char	*ret;
	char	digit;

	len = num_len(n);
	ret = (char *)malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (0);
	ret[len--] = 0;
	if (n < 0)
		ret[0] = '-';
	else if (n == 0)
		ret[0] = '0';
	while (n != 0)
	{
		digit = (n % 10);
		n /= 10;
		if (digit < 0)
			digit = -digit;
		ret[len--] = digit + '0';
	}
	return (ret);
}
