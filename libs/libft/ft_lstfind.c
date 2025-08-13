/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfind.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoraled <dmoraled@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 17:09:05 by dmoraled          #+#    #+#             */
/*   Updated: 2025/02/02 17:42:10 by dmoraled         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstfind(t_list *lst, void *payload, int (*f)(void *, void *))
{
	if (!lst || !f)
		return (0);
	while (lst)
	{
		if (f(lst->content, payload))
			return (lst);
		lst = lst->next;
	}
	return (0);
}
