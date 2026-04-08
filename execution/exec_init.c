/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esezalor <esezalor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 18:12:57 by esezalor          #+#    #+#             */
/*   Updated: 2026/04/08 20:23:39 by esezalor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	envnodes_execarray_init(t_exec *storage, char **envp)
{
	storage->environment = envnodes_init(envp);
	if (!storage->environment)
		return (freeing_ramp(storage), exit(1));
	if (storage->execve_env)
		return (freeing_ramp(storage), exit(1));
	storage->execve_env = envarray_init(storage->environment);
	if (!storage->execve_env)
		return (freeing_ramp(storage), exit(1));
}

void	exec_main_init(t_exec *storage)
{
	storage->pre_read_fd = -1;
	storage->pipe_fd[0] = -1;
	storage->pipe_fd[1] = -1;
	storage->built_in = -1;
	storage->built_out = -1;
	built_init(storage);
}
