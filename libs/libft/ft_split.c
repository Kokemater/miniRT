/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoraled <dmoraled@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 17:25:01 by dmoraled          #+#    #+#             */
/*   Updated: 2025/02/28 14:11:24 by dmoraled         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	add_word(char **split, int count, const char *s, int word_len)
{
	int	i;

	split[count] = ft_substr(s, 0, word_len);
	if (split[count])
		return (1);
	i = 0;
	while (i < count)
		free(split[i++]);
	free(split);
	return (0);
}

static int	count_words(const char *s, char c)
{
	int	ret;

	ret = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (!*s)
			return (ret);
		while (*s && *s != c)
			s++;
		ret++;
	}
	return (ret);
}

char	**ft_split(const char *s, char c)
{
	char	**ret;
	int		wd_it;
	int		word_len;

	if (!s || !(*s))
		return (0);
	wd_it = 0;
	ret = (char **)malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!ret)
		return (0);
	while (*s)
	{
		word_len = 0;
		while (*s == c)
			s++;
		while (s[word_len] && s[word_len] != c)
			word_len++;
		if (*s)
			if (!add_word(ret, wd_it++, s, word_len))
				return (0);
		s += word_len;
	}
	ret[wd_it++] = 0;
	return (ret);
}
