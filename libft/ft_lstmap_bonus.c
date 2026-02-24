/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esezalor <esezalor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 14:58:55 by esezalor          #+#    #+#             */
/*   Updated: 2026/02/24 12:14:56 by esezalor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_env	*ft_lstmap(t_env *lst, void *(*f)(void *), void (*del)(void *))
{
	t_env	*new_lst;
	t_env	*current_node;
	t_env	*tmp;

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
