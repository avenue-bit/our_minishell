/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esezalor <esezalor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 14:45:59 by esezalor          #+#    #+#             */
/*   Updated: 2026/03/10 20:05:12 by esezalor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_fork(t_exec *storage, t_cmd *cmd_node)
{
	if (is_builtin(cmd_node->cmd_flags[0]) == 0)
	{
		if (path_ramp(storage, cmd_node->cmd_flags) != 0)
		{
			write(2, "Command not found\n", 19);
			exit(127);
		}
		execve(storage->command_path, cmd_node->cmd_flags, storage->execve_env);
		perror("exec failed");
		exit(127);
	}
	else
	{
		printf("is builtin and must be executed in parent\n");
		exit(0);
	}
}

void	wait_for_child(t_exec *storage)
{
	int	status;
	int	reaped_pid;

	while ((reaped_pid = waitpid(-1, &status, 0)) > 0)
	{
		if (reaped_pid == storage->last_pid)
		{
			if (WIFEXITED(status))
				storage->exit_code = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				storage->exit_code = 128 + WTERMSIG(status);
		}
	}
}
