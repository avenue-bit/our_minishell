/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esezalor <esezalor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 18:12:57 by esezalor          #+#    #+#             */
/*   Updated: 2026/03/16 19:40:32 by esezalor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 1. envnodes_init: Initialise the environment found in envp into a linked list,
//	the return value (pointer to head of list) is stored in the shell struct

// 2. envarray_init: Converts the linked list of environment into a modifiable array of strings,
//	must do this as it is more tedious to handle the stack version of envp rather than use a linked list

int	is_builtin(t_exec *storage, char *command)
{
	int	cmd_len;
	int	i;

	if (!command || !*command)
		return (0);
	storage->builtins[0] = "echo";
	storage->builtins[1] = "cd";
	storage->builtins[2] = "pwd";
	storage->builtins[3] = "export";
	storage->builtins[4] = "unset";
	storage->builtins[5] = "env";
	storage->builtins[6] = "exit";
	storage->builtins[7] = NULL;
	cmd_len = ft_strlen(command);
	i = 0;
	while (storage->builtins[i])
	{
		if (ft_strncmp(command, storage->builtins[i], cmd_len + 1) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	exec_main(int argc, char **argv, char **envp, t_cmd *cmd_list)
{
	t_cmd	*current;
	t_cmd	*head;

	t_exec storage; // RENAME LATER
	(void)argc;
	ft_bzero(&storage, sizeof(t_exec));
	//built_init(&storage);
	current = cmd_list;
	head = current;
	storage.environment = envnodes_init(envp);
	if (!storage.environment)
		return (-1);
	storage.execve_env = envarray_init(&storage, storage.environment);
	if (!storage.execve_env)
		return (env_clearnode(&storage.environment), 0);
	// Error handling needed
	storage.pre_read_fd = -1;
	while (current)
	{
		// if (!current->next && !current->prev
		// 	&& is_builtin(&storage, current->cmd_flags[0]))
		// 	storage.exit_code = exec_builtin(&storage, &current);
		if (fork_ramp(&storage, current) == -1)
		{
			failexec_close(&storage);
			break ;
		}
		current = current->next;
	}
	wait_for_child(&storage);
	//heredoc_cleanup(head);
	path_env_free(&storage);
	return (0);
}
