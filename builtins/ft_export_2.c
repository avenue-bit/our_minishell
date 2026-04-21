/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esezalor <esezalor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 16:57:46 by esezalor          #+#    #+#             */
/*   Updated: 2026/04/20 14:16:40 by esezalor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export_sort(t_env **exp_array, int exp_len)
{
	int	i;
	int	j;
	int	max_len;

	i = 0;
	while (i < exp_len - 1)
	{
		j = 0;
		while (j < (exp_len - i - 1))
		{
			if (ft_strlen(exp_array[j]->key) > ft_strlen(exp_array[j + 1]->key))
				max_len = ft_strlen(exp_array[j]->key) + 1;
			else
				max_len = ft_strlen(exp_array[j + 1]->key) + 1;
			if (ft_strncmp(exp_array[j]->key, exp_array[j + 1]->key,
					max_len) > 0)
				ft_swap(&exp_array[j], &exp_array[j + 1]);
			j++;
		}
		i++;
	}
}

void	ft_swap(t_env **node1, t_env **node2)
{
	t_env	*tmp;

	tmp = *node1;
	*node1 = *node2;
	*node2 = tmp;
}

void	print_export(t_env **exp_array)
{
	int	i;

	i = 0;
	while (exp_array[i])
	{
		if (ft_strncmp(exp_array[i]->key, "_", 2) != 0)
		{
			if (exp_array[i]->content == NULL)
				ft_printf("declare -x %s\n", exp_array[i]->key);
			else
				ft_printf("declare -x %s=\"%s\"\n", exp_array[i]->key,
					exp_array[i]->content);
		}
		i++;
	}
	// if (!exp_array[i])
	// 	ft_printf("\n");
	// while (exp_array[i])
	// {
	// 	if (ft_strncmp(exp_array[i++]->key, "_", 2) == 0)
	// 		continue ;
	// 	else if (exp_array[i]->content == NULL)
	// 		ft_printf("declare -x %s\n", exp_array[i]->key);
	// 	else
	// 		ft_printf("declare -x %s=\"%s\"\n", exp_array[i]->key,
	// 			exp_array[i]->content);
	// 	i++;
	// }
}
