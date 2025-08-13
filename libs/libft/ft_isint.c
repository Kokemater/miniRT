/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isint.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoraled <dmoraled@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 11:46:42 by dmoraled          #+#    #+#             */
/*   Updated: 2025/02/17 12:51:32 by dmoraled         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isint(const char *str)
{
	long	result;
	int		sign;

	sign = 1;
	result = 0;
	while (ft_isspace(*str))
		++str;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign *= -1;
		++str;
	}
	while (ft_isdigit(*str))
	{
		result = (result * 10) + (*str - '0');
		if (result * sign < INT_MIN || result * sign > INT_MAX)
			return (0);
		++str;
	}
	return (1);
}
