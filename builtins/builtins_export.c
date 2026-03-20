/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esezalor <esezalor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 16:57:46 by esezalor          #+#    #+#             */
/*   Updated: 2026/03/20 21:19:18 by esezalor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_path(t_exec *storage, char *export_path)
{
	t_env	*current;

	if (!storage->environment)
	{
		storage->environment = env_newnode(export_path);
		return ;
	}
	current = storage->environment;
	while (current->next)
		current = current->next;
	current->next = env_newnode(export_path);
	if (!current->next)
		return ;
}

int	findnreplace(t_exec *storage, char *export_path)
{
	t_env	*current;
	char	*new_key;
	int		nkey_len;

	current = storage->environment;
	new_key = fetch_key(export_path);
	if (!new_key)
		return (-1);
	nkey_len = ft_strlen(new_key) + 1;
	while (current)
	{
		if (ft_strncmp(current->key, new_key, nkey_len) == 0)
		{
			if (find_char(export_path, '='))
			{
				free(current->content);
				current->content = fetch_content(export_path);
			}
			return (free(new_key), 0);
		}
		current = current->next;
	}
	return (free(new_key), 1);
}

int	declare_x(t_exec *storage, t_cmd *cmd_node)
{
	t_env	*current;

	(void)cmd_node;
	current = storage->environment;
	while (current)
	{
		if (!current->content)
			ft_printf("declare -x %s\n", current->key);
		else
			ft_printf("declare -x %s=\"%s\"\n", current->key, current->content);
		current = current->next;
	}
	return (0);
}

int	ft_export(t_exec *storage, t_cmd *cmd_node)
{
	int	i;
	int	valid_path;

	i = 1;
	if (!cmd_node->cmd_flags[i])
		return (declare_x(storage, cmd_node));
	while (cmd_node->cmd_flags[i])
	{
		valid_path = findnreplace(storage, cmd_node->cmd_flags[i]);
		if (valid_path == 1)
			add_path(storage, cmd_node->cmd_flags[i]);
		if (valid_path == -1)
			return (1);
		i++;
	}
	return (0);
}
