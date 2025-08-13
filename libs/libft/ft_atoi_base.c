/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoraled <dmoraled@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 17:13:54 by dmoraled          #+#    #+#             */
/*   Updated: 2025/02/26 14:07:58 by dmoraled         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi_base(const char *str, const char *base)
{
	unsigned int		result;
	int					base_len;
	char				*base_ptr;

	base_len = ft_strlen(base);
	result = 0;
	while ((*str >= '\t' && *str <= '\r') || *str == ' ')
		++str;
	base_ptr = ft_strchr(base, ft_tolower(*str));
	while (*str && base_ptr)
	{
		result = (result * base_len) + (int)(base_ptr - base);
		++str;
		base_ptr = ft_strchr(base, ft_tolower(*str));
	}
	return (result);
}
