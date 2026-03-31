/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_basic.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sezalory <sezalory@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 16:57:46 by esezalor          #+#    #+#             */
/*   Updated: 2026/03/25 15:12:01 by sezalory         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_echo(t_exec *storage, t_cmd *cmd_node)
{
	int	i;
	int	j;

	(void)storage;
	if (!cmd_node->cmd_flags[1])
		return (ft_printf("\n"), 0);
	i = newline_flag(cmd_node->cmd_flags);
	j = i;
	if (cmd_node->cmd_flags[j])
	{
		ft_printf("%s", cmd_node->cmd_flags[j]);
		j++;
	}
	while (cmd_node->cmd_flags[j])
	{
		ft_printf(" %s", cmd_node->cmd_flags[j]);
		j++;
	}
	if (i == 1)
		ft_printf("\n");
	return (0);
}

int	ft_pwd(t_exec *storage, t_cmd *cmd_node)
{
	t_env	*current;

	(void)cmd_node;
	current = storage->environment;
	while (current)
	{
		if (ft_strncmp(current->key, "PWD", ft_strlen("PWD")) == 0)
		{
			ft_printf("%s\n", current->content);
			return (0);
		}
		current = current->next;
	}
	return (1);
}

int	ft_env(t_exec *storage, t_cmd *cmd_node)
{
	int	i;

	(void)cmd_node;
	i = 0;
	while (storage->execve_env[i])
	{
		ft_printf("%s\n", storage->execve_env[i]);
		i++;
	}
	return (0);
}

int	ft_exit(t_exec *storage, t_cmd *cmd_node)
{
	(void)cmd_node;
	(void)storage;
	return (0);
}

int	ft_unset(t_exec *storage, t_cmd *cmd_node)
{
	(void)cmd_node;
	(void)storage;
	return (0);
}
