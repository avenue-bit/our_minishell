/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_basic_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esezalor <esezalor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 16:48:53 by esezalor          #+#    #+#             */
/*   Updated: 2026/04/09 10:32:54 by esezalor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

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

int	isvalid_exitcode(char *str)
{
	int	i;

	i = 0;
	if (!str[i])
		return (1);
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (1);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (1);
		i++;
	}
	return (0);
}

void	ft_exit_message(char *exit_str)
{
	ft_putstr_fd("exit\n", 2);
	ft_putstr_fd("bash: exit: ", 2);
	ft_putstr_fd(exit_str, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
}