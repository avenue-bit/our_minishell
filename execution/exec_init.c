/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sezalory <sezalory@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 18:12:57 by esezalor          #+#    #+#             */
/*   Updated: 2026/03/25 15:19:26 by sezalory         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int envnodes_execarray_init(t_exec *storage, char **envp)
{
	storage->environment = envnodes_init(envp);
	if (!storage->environment)
		freeing_ramp(storage, 1);
	if(storage->execve_env)
		freeing_ramp(storage, 1);
	storage->execve_env = envarray_init(storage->environment);
	if (!storage->execve_env)
		freeing_ramp(storage, 1);
	return(1);
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
