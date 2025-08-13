/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoraled <dmoraled@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 14:20:34 by dmoraled          #+#    #+#             */
/*   Updated: 2025/02/17 12:48:33 by dmoraled         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_strtol(const char *str, const char **endptr)
{
	long	result;
	char	sign;

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
		++str;
	}
	while (ft_isspace(*str))
		++str;
	if (endptr)
		*endptr = str;
	return (result * sign);
}
