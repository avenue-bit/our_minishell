/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_0.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esezalor <esezalor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 16:57:46 by esezalor          #+#    #+#             */
/*   Updated: 2026/03/24 17:24:14 by esezalor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Return Values:
// 0: found/updated
// 1: not found
// -1: allocation error

int	ft_export(t_exec *storage, t_cmd *cmd_node)
{
	int	i;
	int	valid_key;
	int	exit_status;
	int	env_changed;

	env_changed = 0;
	exit_status = 0;
	i = 1;
	if (!cmd_node->cmd_flags[i])
		exit_status = declare_x(storage);
	while (cmd_node->cmd_flags[i])
	{
		valid_key = valid_export_key(cmd_node->cmd_flags[i]);
		if (valid_key >= 0 && export_path(storage, cmd_node->cmd_flags[i],
				valid_key, &env_changed))
			return (1);
		if (valid_key < 0)
			exit_status = export_error(cmd_node->cmd_flags[i]);
		i++;
	}
	if (env_changed && update_execve_env(storage))
		return (1);
	return (exit_status);
}

int	declare_x(t_exec *storage)
{
	t_env	**declare_x;
	t_env	*current;
	int		export_len;
	int		i;

	if (!storage->environment)
		return (ft_printf("\n"), 0);
	current = storage->environment;
	export_len = ft_envsize(storage->environment);
	declare_x = ft_calloc(export_len + 1, sizeof(t_env *));
	if (!declare_x)
		return (1);
	i = 0;
	while (current)
	{
		declare_x[i] = current;
		current = current->next;
		i++;
	}
	export_sort(declare_x, export_len);
	print_export(declare_x);
	return (free(declare_x), 0);
}

int	export_path(t_exec *storage, char *export_var, int valid_key, int *env_chg)
{
	int	valid_path;

	valid_path = findnedit(storage, export_var, valid_key);
	if (valid_path == -1)
		return (1);
	if (valid_path == 1)
	{
		if (add_path(storage, export_var) == 1)
			return (1);
		*env_chg = 1;
	}
	else if (valid_path == 0)
		*env_chg = 1;
	return (0);
}

int	findnedit(t_exec *storage, char *export_var, int flag)
{
	t_env	*current;
	char	*nkey;
	int		nkey_len;

	current = storage->environment;
	nkey = fetch_key(export_var);
	if (!nkey)
		return (-1);
	nkey_len = ft_strlen(nkey) + 1;
	while (current)
	{
		if (ft_strncmp(current->key, nkey, nkey_len) == 0)
			return (free(nkey), replace_or_append(current, export_var, flag));
		current = current->next;
	}
	return (free(nkey), 1);
}

int	replace_or_append(t_env *current, char *export_var, int flag)
{
	if (flag == 0)
	{
		if (ft_strchr(export_var, '='))
		{
			free(current->content);
			current->content = fetch_content(export_var);
			if (!current->content)
				return (-1);
		}
	}
	else
	{
		if (append_export_content(current, export_var) == -1)
			return (-1);
	}
	return (0);
}
