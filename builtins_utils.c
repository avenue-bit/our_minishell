/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esezalor <esezalor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 16:48:53 by esezalor          #+#    #+#             */
/*   Updated: 2026/03/17 18:48:45 by esezalor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	newline_flag(char **command)
{
	int	i;
	int	j;

	i = 1;
	while (command[i])
	{
		if (command[i][0] == '-' && command[i][1] == 'n')
		{
			j = 2;
			while (command[i][j])
			{
				if (command[i][j] != 'n')
					return (i);
				j++;
			}
			i++;
		}
		else
			return (i);
	}
	return (i);
}
