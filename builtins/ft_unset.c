/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jille <jille@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 17:30:42 by esezalor          #+#    #+#             */
/*   Updated: 2026/04/19 12:16:52 by jille            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(t_exec *storage, t_cmd *cmd_node)
{
	int	i;
	int	valid_key;
	int	env_changed;

	env_changed = 0;
	i = 1;
	if (!cmd_node->cmd_flags[i])
		return (0);
	while (cmd_node->cmd_flags[i])
	{
		valid_key = valid_unset_key(cmd_node->cmd_flags[i]);
		if (!valid_key)
		{
			if (unset_env(storage, cmd_node->cmd_flags[i], &env_changed) == 1)
				return (0);
		}
		i++;
	}
	if (env_changed && update_execve_env(storage))
		return (0);
	return (0);
}

int	valid_unset_key(char *export_var)
{
	int	i;

	i = 0;
	if (!ft_isalpha(export_var[i]) && export_var[i] != '_')
		return (1);
	while (export_var[i])
	{
		if (!ft_isalpha(export_var[i]) && !ft_isdigit(export_var[i])
			&& export_var[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

int	unset_env(t_exec *storage, char *unset_var, int *env_changed)
{
	int		var_len;
	t_env	*next;
	t_env	*current;

	var_len = ft_strlen(unset_var) + 1;
	current = storage->environment;
	if (current && ft_strncmp(current->key, unset_var, var_len) == 0)
	{
		next = current->next;
		free(current->key);
		free(current->content);
		free(current);
		current = next;
		storage->environment = current;
		return (*env_changed = 1, 0);
	}
	if (!current)
		return (1);
	if (delete_node(current, unset_var, var_len) == 1)
		return (*env_changed = 1, 0);
	return (0);
}
