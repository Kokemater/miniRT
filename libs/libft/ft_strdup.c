/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoraled <dmoraled@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 17:25:01 by dmoraled          #+#    #+#             */
/*   Updated: 2025/02/17 13:41:01 by dmoraled         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*dest;
	size_t	size;

	size = ft_strlen(s) + 1;
	dest = malloc(size * sizeof(char));
	if (!dest)
		return (0);
	ft_strlcpy(dest, s, size);
	return (dest);
}

char	*ft_strdup_to(const char *str, char c)
{
	char	*ret;
	int		i;

	i = 0;
	while (str[i] && str[i] != c)
		++i;
	ret = ft_calloc(i + 2, sizeof(char));
	if (!ret)
		return (0);
	i = 0;
	while (str[i] && str[i] != c)
	{
		ret[i] = str[i];
		++i;
	}
	ret[i] = str[i];
	return (ret);
}

char	*ft_strdup_from(const char *str, char c)
{
	char	*ret;
	int		i;
	int		j;

	i = 0;
	while (str[i] && str[i] != c)
		++i;
	if (!str[i] || !str[i + 1])
		return (0);
	ret = ft_calloc(ft_strlen(str) - i, sizeof(char));
	if (!ret)
		return (0);
	++i;
	j = 0;
	while (str[i])
		ret[j++] = str[i++];
	ret[j] = str[i];
	return (ret);
}
