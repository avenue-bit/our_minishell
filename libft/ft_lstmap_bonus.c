/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esezalor <esezalor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 14:58:55 by esezalor          #+#    #+#             */
/*   Updated: 2025/10/15 10:21:04 by esezalor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*current_node;
	t_list	*tmp;

	if (!lst || !f || !del)
		return (NULL);
	tmp = f(lst->content);
	new_lst = ft_lstnew(tmp);
	if (!new_lst)
		return (del(tmp), NULL);
	current_node = new_lst;
	lst = lst->next;
	while (lst)
	{
		tmp = f(lst->content);
		current_node->next = ft_lstnew(tmp);
		if (!current_node->next)
			return (del(tmp), ft_lstclear(&new_lst, del), NULL);
		lst = lst->next;
		current_node = current_node->next;
	}
	return (new_lst);
}
