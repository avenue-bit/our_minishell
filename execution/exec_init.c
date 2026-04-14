/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esezalor <esezalor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 18:12:57 by esezalor          #+#    #+#             */
/*   Updated: 2026/04/14 10:29:26 by esezalor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headerfiles/minishell.h"

void	envnodes_execarray_init(t_exec *storage, char **envp)
{
	storage->environment = envnodes_init(envp);
	if (!storage->environment)
		return (freeing_ramp(storage), perror("Error"), errno = ENOMEM,
			storage->exit_code = 1, exit(errno));
	if (storage->execve_env)
		return (freeing_ramp(storage), exit(errno));
	storage->execve_env = envarray_init(storage->environment);
	if (!storage->execve_env)
		return (freeing_ramp(storage), perror("Error"), storage->exit_code = 1,
			errno = ENOMEM, exit(errno));
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
