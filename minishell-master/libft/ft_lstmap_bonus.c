/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toramo <toramo.student@hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 09:32:51 by toramo            #+#    #+#             */
/*   Updated: 2023/10/31 12:23:05 by toramo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*head;
	t_list	*tmp;

	if (!lst)
		return (0);
	head = ft_lstnew((*f)(lst -> content));
	if (!head)
		return (0);
	lst = lst -> next;
	while (lst)
	{
		tmp = ft_lstnew((*f)(lst -> content));
		if (tmp == 0)
		{
			ft_lstclear(&head, del);
			return (0);
		}
		ft_lstadd_back(&head, tmp);
		lst = lst -> next;
	}
	return (head);
}
