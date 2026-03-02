/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sezalory <sezalory@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 18:12:57 by esezalor          #+#    #+#             */
/*   Updated: 2026/03/02 12:50:41 by sezalory         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*int	exec_ramp(t_shell *storage)
{
	int i;
	pid_t pid;
	t_cmd *commands;
	int status;
	
	i = 0;
	while(commands)
	{
		if (path_ramp(&storage, commands->cmd_flags[i]) != 0) // parser for start of path finding functions
			return(-1);
		pid = fork();
		if(pid == -1)
			return(-1); // error handle needed
		if(pid == 0)
		{
			if(exec_init(storage, commands->cmd_flags[i]) == -1); // for now everyhting returns -1 but with exit functions that will no longer be the case
				return(-1);
		}
		else
		{
			waitpid(pid, &status, 0);
		}
		commands = commands->next;
	}
	return (0);
}*/


// 1. envnodes_init: Initialise the environment found in envp into a linked list,
//	the return value (pointer to head of list) is stored in the shell struct

// 2. envarray_init: Converts the linked list of environment into a modifiable array of strings,
//	must do this as it is more tedious to handle the stack version of envp rather than use a linked list

int	main(int argc, char **argv, char **envp)
{
	t_shell storage; // RENAME LATER
	
	if (argc < 2)
		return (0);
	ft_bzero(&storage, sizeof(t_shell));
	storage.environment = envnodes_init(envp);
	if (!storage.environment)
		return (0);
	storage.execve_env = envarray_init(&storage, storage.environment);
	if (!storage.execve_env)
		return (env_clearnode(&storage.environment), 0); // Error handling needed
	if (path_ramp(&storage, argv) != 0)
	{
			free(storage.command_path);
			ft_arrayfree(storage.all_paths, storage.n_paths + 1);
			ft_arrayfree(storage.execve_env, storage.n_env_variables);
			env_clearnode(&storage.environment);
			return (-1); // Error handling needed
	}
	execve(storage.command_path, &argv[1], storage.execve_env);
	return (0);
}
