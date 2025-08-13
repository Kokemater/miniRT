/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoraled <dmoraled@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 20:18:27 by dmoraled          #+#    #+#             */
/*   Updated: 2024/10/03 20:24:42 by dmoraled         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *n)
{
	t_list	*last;

	if (!lst || !n)
		return ;
	if (!*lst)
	{
		*lst = n;
		return ;
	}
	last = ft_lstlast(*lst);
	last->next = n;
}
