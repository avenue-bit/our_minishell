/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esezalor <esezalor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 16:57:46 by esezalor          #+#    #+#             */
/*   Updated: 2026/03/23 21:30:51 by esezalor         ###   ########.fr       */
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
		declare_x(); // not built yet,will do this at the end along with sorting
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

int	export_path(t_exec *storage, char *export_var, int valid_key, int *env_chg)
{
	int	valid_path;

	valid_path = findnedit(storage, export_var, valid_key);
	if (valid_path == -1)
		return (1);
	if (valid_path == 1)
		*env_chg = add_path(storage, export_var); // to build
	else if (valid_path == 0)
		*env_chg = 1;
	return (0);
}

int	valid_export_key(char *export_var)
{
	int	i;

	i = 0;
	if (!ft_isalpha(export_var[i]) && export_var[i] != '_')
		return (-1);
	while (export_var[i] && export_var[i] != '=')
	{
		if (export_var[i] == '+' && export_var[i + 1] == '=')
			return (1);
		if (!ft_isalpha(export_var[i]) && !ft_isdigit(export_var[i])
			&& export_var[i] != '_')
			return (-1);
		i++;
	}
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
		if (find_char(export_var, '='))
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
