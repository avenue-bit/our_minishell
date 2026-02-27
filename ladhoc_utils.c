/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ladhoc_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esezalor <esezalor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 11:52:31 by esezalor          #+#    #+#             */
/*   Updated: 2026/02/27 11:50:50 by esezalor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_arrayfree(char **str_array, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		if (str_array[i])
		{
			free(str_array[i]);
			str_array[i] = NULL;
		}
		i++;
	}
	free(str_array);
	str_array = NULL;
}

int	ft_envsize(t_env *lst)
{
	int size;

	if (!lst)
		return (0);
	size = 1;
	while (lst->next)
	{
		lst = lst->next;
		size++;
	}
	return (size);
}