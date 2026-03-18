/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esezalor <esezalor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 16:48:53 by esezalor          #+#    #+#             */
/*   Updated: 2026/03/18 19:46:27 by esezalor         ###   ########.fr       */
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

char	*get_target_path(t_exec *storage, char *command)
{
	if (!command)
		return (cd_path(storage, "HOME", 5));
	else
		return (command);
}

char	*cd_path(t_exec *storage, char *key, int size)
{
	t_env	*current;

	current = storage->environment;
	while (current)
	{
		if (ft_strncmp(current->key, key, size) == 0)
			return (current->content);
		current = current->next;
	}
	return (NULL);
}

int	replace_pwd(t_exec *storage, char *old_pwd)
{
	char	*buffer;
	t_env	*oldpwd_node;
	t_env	*pwd_node;

	oldpwd_node = get_envnode(storage, "OLD_PWD", 8);
	pwd_node = get_envnode(storage, "PWD", 4);
	if (pwd_node)
	{
		buffer = ft_calloc(PATH_MAX, sizeof(char));
		if (!buffer)
			return (-1); // Error Handling Needed
		if (!getcwd(buffer, PATH_MAX))
			return (free(buffer), -1); // Error Handling Needed
		free(pwd_node->content);
		pwd_node->content = buffer;
	}
	if (oldpwd_node)
	{
		free(oldpwd_node->content);
		oldpwd_node->content = old_pwd;
	}
	else
		return (free(old_pwd), 0);
	return (0);
}
