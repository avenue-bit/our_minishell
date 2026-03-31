/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esezalor <esezalor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 16:57:46 by esezalor          #+#    #+#             */
/*   Updated: 2026/03/31 14:25:25 by esezalor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

int	add_path(t_exec *storage, char *export_var)
{
	t_env	*current;

	if (!storage->environment)
	{
		storage->environment = env_newnode(export_var);
		if (!storage->environment)
			return (1);
		return (0);
	}
	current = storage->environment;
	while (current->next)
		current = current->next;
	current->next = env_newnode(export_var);
	if (!current->next)
		return (1);
	return (0);
}

int	append_export_content(t_env *current, char *export_var)
{
	char	*export_content;
	char	*new_content;

	export_content = fetch_content(export_var);
	if (!export_content)
		return (-1);
	if (!current->content)
		return (current->content = export_content, 0);
	else
		new_content = ft_strjoin(current->content, export_content);
	if (!new_content)
		return (free(export_content), -1);
	free(current->content);
	current->content = new_content;
	free(export_content);
	return (0);
}

int	export_error(char *export_var)
{
	ft_putstr_fd("bash: export: \'", 2);
	ft_putstr_fd(export_var, 2);
	ft_putstr_fd("\': not a valid identifier\n", 2);
	return (1);
}

int	update_execve_env(t_exec *storage)
{
	ft_arrayfree(storage->execve_env);
	storage->execve_env = NULL;
	storage->execve_env = envarray_init(storage->environment);
	if (!storage->execve_env)
		return (1);
	return (0);
}
