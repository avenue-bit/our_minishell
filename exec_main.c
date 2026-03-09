/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esezalor <esezalor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 14:45:59 by esezalor          #+#    #+#             */
/*   Updated: 2026/03/09 15:05:26 by esezalor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_main(t_exec *storage, t_cmd *cmd_node)
{
	if (is_builtin(cmd_node->cmd_flags[0]) == 0)
	{
		if (exec_fork(storage, cmd_node) != 0)
			return (-1);
	}
	else
		printf("is builtin and must be executed in parent");
	return (0);
}

int	exec_fork(t_exec *storage, t_cmd *cmd_node)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return (-1);
	if (pid == 0)
	{
		if (path_ramp(storage, cmd_node->cmd_flags) != 0)
		{
			perror("Command not found\n");
			exit(127);
		}
		execve(storage->command_path, cmd_node->cmd_flags, storage->execve_env);
		perror("exec failed");
		exit(127);
	}
	else
		wait_for_child(storage, pid);
	return (0);
}

void	wait_for_child(t_exec *storage, pid_t pid)
{
	int	status;
	int	child_pid;

	child_pid = waitpid(pid, &status, 0);
	if (child_pid != -1)
	{
		if (WIFEXITED(status))
		{
			storage->exit_code = WEXITSTATUS(status);
			printf("Child %ld exited normally\n", (long)child_pid); // to change
		}
		else if (WIFSIGNALED(status))
		{
			storage->exit_code = 128 + WTERMSIG(status);
			printf("Child %ld killed by signal\n", (long)child_pid);
				// to change
		}
	}
}
