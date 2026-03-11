/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_for_all.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esezalor <esezalor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 14:10:43 by esezalor          #+#    #+#             */
/*   Updated: 2026/03/11 17:13:58 by esezalor         ###   ########.fr       */
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

void failexec_close(t_exec *storage)
{
	if (storage->pre_read_fd >= 0)
		close(storage->pre_read_fd);
	if (storage->pipe_fd[1] >= 0)
		close(storage->pipe_fd[1]);
	if (storage->pipe_fd[0] >= 0)
		close(storage->pipe_fd[0]);
}