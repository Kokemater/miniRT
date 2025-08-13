/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoraled <dmoraled@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 17:25:01 by dmoraled          #+#    #+#             */
/*   Updated: 2024/10/13 14:04:10 by dmoraled         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdlib.h>

char	*ft_strtrim(const char *s1, const char *set)
{
	const char	*end;

	if (!s1 || !set)
		return (0);
	end = s1 + ft_strlen(s1) - 1;
	while (s1 < end && ft_strchr(set, *s1))
		++s1;
	while (end >= s1 && ft_strchr(set, *end))
		--end;
	return (ft_substr(s1, 0, end - s1 + 1));
}
