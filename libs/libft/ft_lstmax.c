/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmax.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoraled <dmoraled@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 15:21:16 by dmoraled          #+#    #+#             */
/*   Updated: 2025/02/02 15:25:11 by dmoraled         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmax(t_list *lst, int (*less)(void *, void *))
{
	t_list	*max;

	max = 0;
	while (lst)
	{
		if (!max || less(max->content, lst->content))
			max = lst;
		lst = lst->next;
	}
	return (max);
}
