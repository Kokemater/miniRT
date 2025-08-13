/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isnum.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoraled <dmoraled@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 11:44:55 by dmoraled          #+#    #+#             */
/*   Updated: 2025/01/12 16:14:25 by dmoraled         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isnum(const char *s)
{
	int	found;

	found = 0;
	while (*s)
	{
		if (!ft_isspace(*s) && !ft_isdigit(*s) && *s != '-' && *s != '+')
			return (0);
		if ((*s == '-' || *s == '+') && !ft_isdigit(s[1]))
			return (0);
		if (ft_isdigit(*s))
			found = 1;
		++s;
	}
	return (found);
}
