/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sezalory <sezalory@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 18:12:57 by esezalor          #+#    #+#             */
/*   Updated: 2026/03/05 15:48:09 by sezalory         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *command)
{
	char	*builtins[8];
	int		cmd_len;
	int		i;
	
	if (!command || !*command)
		return (0);
	builtins[0] = "echo";
	builtins[1] = "cd";
	builtins[2] = "pwd";
	builtins[3] = "export";
	builtins[4] = "unset";
	builtins[5] = "env";
	builtins[6] = "exit";
	builtins[7] = NULL;
	cmd_len = ft_strlen(command);
	i = 0;
	while (builtins[i])
	{
		if (ft_strncmp(command, builtins[i], cmd_len + 1) == 0)
			return (1);
		i++;
	}
	return (0);
}


// 1. envnodes_init: Initialise the environment found in envp into a linked list,
//	the return value (pointer to head of list) is stored in the shell struct

// 2. envarray_init: Converts the linked list of environment into a modifiable array of strings,
//	must do this as it is more tedious to handle the stack version of envp rather than use a linked list

int	main(int argc, char **argv, char **envp)
{
	int	i;
	t_exec storage; // RENAME LATER
	
	if (argc < 2)
		return (0);
	ft_bzero(&storage, sizeof(t_exec));
	storage.environment = envnodes_init(envp);
	if (!storage.environment)
		return (0);
	storage.execve_env = envarray_init(&storage, storage.environment);
	if (!storage.execve_env)
		return (env_clearnode(&storage.environment), 0);
	// Error handling needed
	storage.n_children = ft_envsize(storage.commands);
	if (is_builtin(argv[1]) == 0) // storage.commands->cmd_flags
	{
		if (path_ramp(&storage, argv) != 0)
		{
			free(storage.command_path);
			ft_arrayfree(storage.all_paths, storage.n_paths + 1);
			ft_arrayfree(storage.execve_env, storage.n_env_variables);
			env_clearnode(&storage.environment);
			return (-1); // Error handling needed
		}
		execve(storage.command_path, &argv[1], storage.execve_env);
	}
	else
		printf("is builtin and must be executed in parent");
	return (0);
}
