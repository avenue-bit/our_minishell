/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jille <jille@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 18:12:57 by esezalor          #+#    #+#             */
/*   Updated: 2026/04/19 15:21:45 by jille            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_main(t_exec *storage)
{
	t_cmd	*cmd_list;
	int		i;

	i = 0;
	cmd_list = storage->command_nodes;
	exec_main_init(storage);
	if(cmd_pids_init(storage, cmd_list) == 0)
		return(freeing_ramp(storage), perror("minishell: Error"),
			storage->exit_code = 1, 0);
	if(!cmd_list)
		return(storage->exit_code = 1, 0);
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

