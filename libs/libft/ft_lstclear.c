/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoraled <dmoraled@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 20:26:40 by dmoraled          #+#    #+#             */
/*   Updated: 2024/10/03 20:26:40 by dmoraled         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*tmp_next;
	t_list	**start;

	if (!lst || !del)
		return ;
	start = lst;
	while (*lst)
	{
		tmp_next = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = tmp_next;
	}
	*start = 0;
}
