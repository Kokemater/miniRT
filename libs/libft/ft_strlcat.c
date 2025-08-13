/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoraled <dmoraled@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 17:25:01 by dmoraled          #+#    #+#             */
/*   Updated: 2024/10/07 19:06:51 by dmoraled         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	dst_s;
	size_t	src_s;

	dst_s = ft_strlen(dst);
	src_s = ft_strlen(src);
	if (size <= dst_s)
		return (src_s + size);
	i = 0;
	while (dst_s + i < size - 1 && src[i])
	{
		dst[dst_s + i] = src[i];
		++i;
	}
	dst[dst_s + i] = 0;
	return (dst_s + src_s);
}
