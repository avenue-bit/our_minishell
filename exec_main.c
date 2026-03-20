/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esezalor <esezalor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 18:12:57 by esezalor          #+#    #+#             */
/*   Updated: 2026/03/20 16:16:49 by esezalor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 1. envnodes_init: Initialise the environment found in envp into a linked list,
//	the return value (pointer to head of list) is stored in the shell struct

// 2. envarray_init: Converts the linked list of environment into a modifiable array of strings,
//	must do this as it is more tedious to handle the stack version of envp rather than use a linked list

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

int	exec_main(t_exec *storage, char **envp, t_cmd *cmd_list, t_token *token_lst)
{
	exec_main_init(storage, cmd_list, token_lst);
	storage->environment = envnodes_init(envp);
	if (!storage->environment)
		return (path_env_free(storage), -1);
	if(storage->execve_env)
		ft_arrayfree(storage->execve_env);		
	storage->execve_env = envarray_init(storage, storage->environment);
	if (!storage->execve_env)
		return (path_env_free(storage), env_clearnode(&storage->environment),
			0);// Error handling needed
	while (cmd_list)
	{
		if (!cmd_list->next && !cmd_list->prev && is_builtin(storage,
				cmd_list->cmd_flags[0]))
			builtin_dup(storage, cmd_list);
		else if (fork_ramp(storage, cmd_list) == -1)
			break ;
		cmd_list = cmd_list->next;
	}
	wait_for_child(storage);
	return (0);
}
