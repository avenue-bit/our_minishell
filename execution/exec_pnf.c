/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pnf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esezalor <esezalor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 14:45:59 by esezalor          #+#    #+#             */
/*   Updated: 2026/03/25 10:07:18 by esezalor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	fork_ramp(t_exec *storage, t_cmd *cmd_node)
{
	int i;

	i = 0;
	if (cmd_node->next)
	{
		if (pipe(storage->pipe_fd) == -1)
			return (perror("pipe"), -1);
	}
	storage->c_pids[i] = fork();
	if (storage->c_pids[i] < 0)
		return (-1);
	if (storage->c_pids[i] == 0)
		child_wrapper(storage, cmd_node);
	else
		parent_wrapper(storage, cmd_node);
	i++;
	return (0);
}

void	child_wrapper(t_exec *storage, t_cmd *current)
{
	if (storage->pre_read_fd != -1)
	{
		if (dup2(storage->pre_read_fd, 0) == -1)
			freeing_ramp(storage, 1); // Proper exit code needed
		close(storage->pre_read_fd);
		storage->pre_read_fd = -1;
	}
	if (current->next)
	{
		if (dup2(storage->pipe_fd[1], 1) == -1)
			freeing_ramp(storage, 1); // Proper exit code needed
		close(storage->pipe_fd[1]);
		close(storage->pipe_fd[0]);
		storage->pipe_fd[1] = -1;
		storage->pipe_fd[0] = -1;
	}
	if (!infile_outfile_check(storage, current))
		freeing_ramp(storage, 1); // Proper exit code needed
	exec_fork(storage, current);
}

void	exec_fork(t_exec *storage, t_cmd *cmd_node)
{
	if (is_builtin(storage, cmd_node->cmd_flags[0]) == 0)
	{
		if (path_ramp(storage, cmd_node->cmd_flags) != 0)
		{
			write(2, "Command not found\n", 19);
			freeing_ramp(storage, 127);
		}
		execve(storage->command_path, cmd_node->cmd_flags, storage->execve_env);
		perror("exec failed");
		freeing_ramp(storage, 127);
	}
	else
	{
		storage->exit_code = exec_builtin(storage, cmd_node);
		freeing_ramp(storage, storage->exit_code);
	}
}

void	parent_wrapper(t_exec *storage, t_cmd *current)
{
	if (storage->pre_read_fd != -1)
	{
		close(storage->pre_read_fd);
		storage->pre_read_fd = -1;
	}
	if (current->next)
	{
		close(storage->pipe_fd[1]);
		storage->pipe_fd[1] = -1;
		storage->pre_read_fd = storage->pipe_fd[0];
		storage->pipe_fd[0] = -1;
	}
}

void	wait_for_child(t_exec *storage)
{
	int i;
	int	status;
	int	reaped_pid;

	i = 0;
	while (i < storage->n_commands_nodes)
	{
		reaped_pid = waitpid(storage->c_pids[i], &status, 0);
		if (reaped_pid < 0)
		{
			if (errno == EINTR)
				continue ;
		}
		if (reaped_pid > 0)
		{
			if (WIFEXITED(status))
				storage->exit_code = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				storage->exit_code = 128 + WTERMSIG(status);
		}
		i++;
	}
}
