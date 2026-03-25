/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esezalor <esezalor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 18:12:57 by esezalor          #+#    #+#             */
/*   Updated: 2026/03/25 12:44:09 by esezalor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// 1. envnodes_init: Initialise the environment found in envp into a linked list,
//	the return value (pointer to head of list) is stored in the shell struct

// 2. envarray_init: Converts the linked list of environment into a modifiable array of strings,
//	must do this as it is more tedious to handle the stack version of envp rather than use a linked list

// 3. Initialised my environment and my exec array in the main 
// as if i did it in exec_main it would wipe the arrays at every execution of a builtin


// TO DO LIST:
// 1. Change the waiting function with waitpid, it is a must
// 2. clear all funcheck leaks
// 3. rl hook to handle signals (will change life)

int	exec_main(t_exec *storage, char **envp)
{
	t_cmd *cmd_list;
	
	cmd_list = storage->command_nodes;
	exec_main_init(storage);
	storage->n_commands_nodes = n_commands(cmd_list);
	storage->c_pids = ft_calloc(storage->n_commands_nodes, sizeof(pid_t));
	if(!storage->c_pids)
		freeing_ramp(storage, 1);
	while (cmd_list)
	{
		if (!cmd_list->next && !cmd_list->prev && is_builtin(storage,
				cmd_list->cmd_flags[0]))
			builtin_dup(storage, cmd_list);
		else if (fork_ramp(storage, cmd_list) == -1)
			break ;
		cmd_list = cmd_list->next;
	}
	if(wait_for_child(storage) == 1)
		freeing_ramp(storage, errno);
	return (0);
}
