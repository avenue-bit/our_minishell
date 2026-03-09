/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esezalor <esezalor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 14:10:43 by esezalor          #+#    #+#             */
/*   Updated: 2026/03/09 14:11:03 by esezalor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	path_env_free(t_exec *storage)
{
	free(storage->command_path);
	ft_arrayfree(storage->all_paths, storage->n_paths + 1);
	ft_arrayfree(storage->execve_env, storage->n_env_variables);
	env_clearnode(&storage->environment);
}