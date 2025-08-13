/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoraled <dmoraled@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 18:11:43 by dmoraled          #+#    #+#             */
/*   Updated: 2025/02/17 14:00:16 by dmoraled         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "get_next_line.h"
#include "../libft.h"

#include <unistd.h>

char	*gnl_read_fd(int fd, char *buffer)
{
	char	tmp[GNL_BUFFER_SIZE + 1];
	int		rd;
	char	*swp;

	rd = 1;
	while (!ft_strchr(buffer, '\n') && rd > 0)
	{
		rd = read(fd, tmp, GNL_BUFFER_SIZE);
		if (rd <= 0)
			break ;
		tmp[rd] = 0;
		swp = ft_strjoin(buffer, tmp);
		if (buffer)
			free(buffer);
		buffer = swp;
	}
	if (rd == -1)
	{
		free(buffer);
		buffer = 0;
	}
	return (buffer);
}

char	*get_next_line(int fd)
{
	char		*tmp;
	static char	*buffer[1024];
	char		*line;

	if (!ft_strchr(buffer[fd], '\n'))
		buffer[fd] = gnl_read_fd(fd, buffer[fd]);
	if (!buffer[fd] || !(*(buffer[fd])))
		return (0);
	line = ft_strdup_to(buffer[fd], '\n');
	tmp = ft_strdup_from(buffer[fd], '\n');
	free(buffer[fd]);
	buffer[fd] = tmp;
	return (line);
}
