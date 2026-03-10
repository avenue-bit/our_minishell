/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esezalor <esezalor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 18:12:57 by esezalor          #+#    #+#             */
/*   Updated: 2026/03/10 20:06:27 by esezalor         ###   ########.fr       */
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
	t_cmd	*current;
	pid_t	pid;

	t_exec storage; // RENAME LATER
	(void)argc;
	ft_bzero(&storage, sizeof(t_exec));
	current = cmdnodes_init(argv);
	storage.environment = envnodes_init(envp);
	if (!storage.environment)
		return (0);
	storage.execve_env = envarray_init(&storage, storage.environment);
	if (!storage.execve_env)
		return (env_clearnode(&storage.environment), 0);
	// Error handling needed
	storage.pre_read_fd = -1;
	while (current)
	{
		if (current->next)
		{
			if (pipe(storage.pipe_fd) == -1)
				return (perror("pipe"), -1);
		}
		pid = fork();
		if (pid < 0)
			return (-1);
		if (pid == 0)
		{
			if (storage.pre_read_fd != -1)
			{
				dup2(storage.pre_read_fd, 0);
				close(storage.pre_read_fd);
			}
			if (current->next)
			{
				dup2(storage.pipe_fd[1], 1);
				close(storage.pipe_fd[1]);
				close(storage.pipe_fd[0]);
			}
			exec_fork(&storage, current);
		}
		else
		{
			if (storage.pre_read_fd != -1)
				close(storage.pre_read_fd);
			if (current->next)
			{
				close(storage.pipe_fd[1]);
				storage.pre_read_fd = storage.pipe_fd[0];
			}
		}
		storage.last_pid = pid;
		current = current->next;
	}
	wait_for_child(&storage);
	return (0);
}
