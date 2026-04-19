/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jille <jille@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 16:57:46 by esezalor          #+#    #+#             */
/*   Updated: 2026/04/19 12:16:41 by jille            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(t_exec *storage, t_cmd *cmd_node)
{
	char	*pwd_path;
	char	*target_path;
	char	*old_pwd;

	if (cmd_node->cmd_flags[1] && cmd_node->cmd_flags[2])
		return (ft_putstr_fd("jeis: cd: too many arguments\n", 2), 1);
	pwd_path = cd_path(storage, "PWD", 4);
	if (!pwd_path)
		old_pwd = ft_strdup("");
	else
		old_pwd = ft_strdup(pwd_path);
	if (!old_pwd)
		return (1);
	target_path = get_target_path(storage, cmd_node->cmd_flags[1]);
	if (!target_path)
		return (free(old_pwd), ft_putstr_fd("jeis: cd: HOME not set\n", 2), 1);
	if (chdir(target_path) == -1)
	{
		builtin_error_messages(cmd_node->cmd_flags[1], "cd");
		return (free(old_pwd), 1);
	}
	if (replace_pwd(storage, old_pwd) == -1)
		return (free(old_pwd), 1);
	if (update_execve_env(storage))
		return (1);
	return (0);
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

char	*get_target_path(t_exec *storage, char *command)
{
	if (!command)
		return (cd_path(storage, "HOME", 5));
	else
		return (command);
}

int	replace_pwd(t_exec *storage, char *old_pwd)
{
	char	*buffer;
	t_env	*oldpwd_node;
	t_env	*pwd_node;

	oldpwd_node = get_envnode(storage, "OLDPWD", 7);
	pwd_node = get_envnode(storage, "PWD", 4);
	if (pwd_node)
	{
		buffer = ft_calloc(PATH_MAX, sizeof(char));
		if (!buffer)
			return (-1);
		if (!getcwd(buffer, PATH_MAX))
			return (free(buffer), -1);
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

t_env	*get_envnode(t_exec *storage, char *key, int size)
{
	t_env	*current;

	current = storage->environment;
	while (current)
	{
		if (ft_strncmp(current->key, key, size) == 0)
			return (current);
		current = current->next;
	}
	return (NULL);
}
