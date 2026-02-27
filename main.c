/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esezalor <esezalor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 18:12:57 by esezalor          #+#    #+#             */
/*   Updated: 2026/02/27 12:18:42 by esezalor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_shell storage; // RENAME LATER

	ft_bzero(&storage, sizeof(t_shell));
	if (argc < 1)
		return (0);
	storage.environment = envnodes_init(envp);
	// Initialise the environment found in envp into a linked list,
	//	the return value (pointer to head of list) is stored in the shell struct
	storage.execve_env = envarray_init(storage.environment);
	// Converts the linked list of environment into a modifiable array of strings,
	//	must do this as it is more tedious to handle the stack version of envp rather than use a linked list
	if (!storage.execve_env)
		return (env_clearnode(&storage.environment), 0);
			// Error handling needed
	if (!path_ramp(&storage, argv)) // parser for start of path finding functions
		return (env_clearnode(&storage.environment), 0);
			// Error handling needed
	execve(storage.command_path, &argv[1], storage.execve_env);
	return (0);
}