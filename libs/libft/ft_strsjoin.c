/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsjoin.c                                       :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoraled <dmoraled@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 17:25:01 by dmoraled          #+#    #+#             */
/*   Updated: 2024/10/09 18:29:55 by dmoraled         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsjoin(const char *s1, const char *s2, const char sep)
{
	char	*dest;
	size_t	size;
	size_t	s1_s;

	if (!s1 && !s2)
		return (0);
	s1_s = ft_strlen(s1);
	size = s1_s + ft_strlen(s2) + 2;
	dest = malloc(size * sizeof(char));
	if (!dest)
		return (0);
	if (s1)
		ft_strlcpy(dest, s1, size);
	dest[s1_s] = sep;
	dest[s1_s + 1] = 0;
	if (s2)
		ft_strlcat(dest, s2, size);
	return (dest);
}
