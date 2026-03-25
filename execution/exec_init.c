/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esezalor <esezalor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 18:12:57 by esezalor          #+#    #+#             */
/*   Updated: 2026/03/25 09:30:52 by esezalor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int envnodes_execarray_init(t_exec *storage, char **envp)
{
	storage->environment = envnodes_init(envp);
	if (!storage->environment)
		return (path_env_free(storage), 0);
	if(storage->execve_env)
		ft_arrayfree(storage->execve_env);
	storage->execve_env = envarray_init(storage, storage->environment);
	if (!storage->execve_env)
		return (path_env_free(storage), env_clearnode(&storage->environment),
			0);
	return(1);
}

void	exec_main_init(t_exec *storage, t_cmd *cmd_list, t_token *token_lst)
{
	storage->command_nodes = cmd_list;
	storage->token_nodes = token_lst;
	storage->pre_read_fd = -1;
	storage->pipe_fd[0] = -1;
	storage->pipe_fd[1] = -1;
	storage->built_in = -1;
	storage->built_out = -1;
	built_init(storage);
}
