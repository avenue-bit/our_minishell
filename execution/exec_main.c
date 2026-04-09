/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esezalor <esezalor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 18:12:57 by esezalor          #+#    #+#             */
/*   Updated: 2026/04/09 10:37:57 by esezalor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

// 1. envnodes_init: Initialise the environment found in envp into a linked list,
//	the return value (pointer to head of list) is stored in the shell struct

// 2. envarray_init: Converts the linked list of environment into a modifiable array of strings,
//	must do this as it is more tedious to handle the stack version of envp rather than use a linked list

// 3. Initialised my environment and my exec array in the main
// as if i did it in exec_main it would wipe the arrays at every execution of a builtin

int	exec_main(t_exec *storage)
{
	t_cmd	*cmd_list;
	int		i;

	i = 0;
	cmd_list = storage->command_nodes;
	exec_main_init(storage);
	storage->n_commands_nodes = n_commands(cmd_list);
	storage->c_pids = ft_calloc(storage->n_commands_nodes, sizeof(pid_t));
	if (!storage->c_pids)
		return (freeing_ramp(storage), exit(1), 0);
	while (cmd_list)
	{
		if (!cmd_list->next && !cmd_list->prev && is_builtin(storage,
				cmd_list->cmd_flags[0]))
			return (builtin_dup(storage, cmd_list), 0);
		else if (fork_ramp(storage, cmd_list, i) == -1)
			break ;
		cmd_list = cmd_list->next;
		i++;
	}
	if (wait_for_child(storage) == 1)
		return (1);
	return (0);
}
