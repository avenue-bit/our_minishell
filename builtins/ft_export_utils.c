/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esezalor <esezalor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 16:57:46 by esezalor          #+#    #+#             */
/*   Updated: 2026/03/23 21:30:42 by esezalor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	export_error(char *export_var)
{
	ft_putstr_fd("bash: export: \'", 2);
	ft_putstr_fd(export_var, 2);
	ft_putstr_fd("\': not a valid identifier\n", 2);
	return (1);
}

int	append_export_content(t_env *current, char *export_var)
{
	char	*export_content;
	char	*new_content;

	export_content = fetch_content(export_var);
	if (!export_content)
		return (-1);
	if (!current->content)
		return(current->content = export_content, 0);
	else
		new_content = ft_strjoin(current->content, export_content);
	if (!new_content)
		return (free(export_content), -1);
	free(current->content);
	current->content = new_content;
	free(export_content);
	return (0);
}

int update_execve_env(t_exec *storage)
{
    ft_arrayfree(storage->execve_env);
    storage->execve_env = envarray_init(storage, storage->environment);
    if (!storage->execve_env)
        return (1);
    return (0);
}
