/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esezalor <esezalor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 18:10:11 by esezalor          #+#    #+#             */
/*   Updated: 2026/04/20 14:26:52 by esezalor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	envclear_allnodes(t_env **env_lst)
{
	t_env	*current_node;
	t_env	*next_node;

	if (!*env_lst)
		return ;
	current_node = *env_lst;
	while (current_node)
	{
		next_node = current_node->next;
		free(current_node->key);
		free(current_node->content);
		free(current_node);
		current_node = next_node;
	}
	*env_lst = NULL;
}

int	delete_node(t_env *current, char *unset_var, int var_len)
{
	t_env	*temp;

	while (current && current->next)
	{
		if (ft_strncmp(current->next->key, unset_var, var_len) == 0)
		{
			temp = current->next;
			current->next = current->next->next;
			free(temp->key);
			free(temp->content);
			free(temp);
			return (1);
		}
		current = current->next;
	}
	return (0);
}

char	*env_join(char *key, char *content)
{
	char	*variable;
	int		key_len;
	int		content_len;

	key_len = ft_strlen(key);
	content_len = ft_strlen(content);
	variable = ft_calloc(key_len + content_len + 2, sizeof(char));
	if (!variable)
		return (NULL);
	ft_memcpy(variable, key, key_len);
	variable[key_len] = 61;
	ft_memcpy(variable + key_len + 1, content, content_len);
	return (variable);
}

void	pathfinder_join(char *path, char *is_valid, char *command)
{
	ft_memcpy(is_valid, path, ft_strlen(path));
	is_valid[ft_strlen(path)] = '/';
	ft_memcpy(is_valid + ft_strlen(path) + 1, command, ft_strlen(command));
}

int	env_error_paths(char *command, t_exec *storage, int error1)
{
	char	*msg;

	msg = NULL;
	if (error1 == 0 && storage->exit_code == 126)
		msg = ": Is a directory\n";
	else if (error1 == 1 && storage->exit_code == 126)
		msg = ": Permission denied\n";
	else if (error1 == 1 && storage->exit_code == 127)
		msg = ": command not found\n";
	else if (error1 == 0 && storage->exit_code == 127)
		msg = ": No such file or directory\n";
	if (msg)
	{
		write(2, "jeis: ", 6);
		error_message_helper(command, msg, 2);
		return (storage->exit_code);
	}
	return (perror("Error"), 1);
}
