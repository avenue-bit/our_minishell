/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esezalor <esezalor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 18:12:57 by esezalor          #+#    #+#             */
/*   Updated: 2026/03/16 14:07:19 by esezalor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 1. envnodes_init: Initialise the environment found in envp into a linked list,
//	the return value (pointer to head of list) is stored in the shell struct

// 2. envarray_init: Converts the linked list of environment into a modifiable array of strings,
//	must do this as it is more tedious to handle the stack version of envp rather than use a linked list

int	main(int argc, char **argv, char **envp)
{
	t_cmd	*current;

	t_exec storage; // RENAME LATER
	(void)argc;
	ft_bzero(&storage, sizeof(t_exec));
	current = cmdnodes_init(argv);
	storage.environment = envnodes_init(envp);
	if (!storage.environment)
		return (-1);
	storage.execve_env = envarray_init(&storage, storage.environment);
	if (!storage.execve_env)
		return (env_clearnode(&storage.environment), 0);
	// Error handling needed
	storage.pre_read_fd = -1;
	is_doc_here(storage, current);
	while (current)
	{
		if (fork_ramp(&storage, current) == -1)
		{
			failexec_close(&storage);
			break ;
		}
		current = current->next;
	}
	wait_for_child(&storage);
	path_env_free(&storage);
	return (0);
}
