/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_basic_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jille <jille@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 16:48:53 by esezalor          #+#    #+#             */
/*   Updated: 2026/04/19 19:08:54 by jille            ###   ########.fr       */
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

void	builtin_error_messages(char *cmd, char *builtin)
{
	if (ft_strncmp(builtin, "cd", 5) == 0)
	{
		write(1, "jeis: cd: ", 10);
		error_message_helper(cmd, ": No such file or directory\n", 1);
	}
	else if (ft_strncmp(builtin, "exit", 5) == 0)
	{
		ft_putstr_fd("exit\n", 1);
		ft_putstr_fd("bash: exit: ", 2);
		error_message_helper(cmd, ": numeric argument required\n", 2);
	}
}
