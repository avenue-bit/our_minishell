/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_ft1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esezalor <esezalor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 16:57:46 by esezalor          #+#    #+#             */
/*   Updated: 2026/03/17 18:55:37 by esezalor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Dont forget to replace with ft_printf

int	ft_echo(t_exec *storage, t_cmd *cmd_node)
{
	int	i;
	int	j;

	(void)storage;
	if (!cmd_node->cmd_flags[1])
		return (printf("\n"), 0);
	i = newline_flag(cmd_node->cmd_flags);
	j = i;
	if (cmd_node->cmd_flags[j])
	{
		printf("%s", cmd_node->cmd_flags[j]);
		j++;
	}
	while (cmd_node->cmd_flags[j])
	{
		printf(" %s", cmd_node->cmd_flags[j]);
		j++;
	}
	if (i == 1)
		printf("\n");
	return (0);
}

int	ft_cd(t_exec *storage, t_cmd *cmd_node)
{
	return (0);
}

int	ft_pwd(t_exec *storage, t_cmd *cmd_node)
{
	return (0);
}

int	ft_export(t_exec *storage, t_cmd *cmd_node)
{
	return (0);
}

int	ft_unset(t_exec *storage, t_cmd *cmd_node)
{
	return (0);
}
