/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pnf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esezalor <esezalor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 14:45:59 by esezalor          #+#    #+#             */
/*   Updated: 2026/03/16 17:05:17 by esezalor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fork_ramp(t_exec *storage, t_cmd *cmd_node)
{
	pid_t	pid;

	if (cmd_node->next)
	{
		if (pipe(storage->pipe_fd) == -1)
			return (perror("pipe"), -1);
	}
	pid = fork();
	if (pid < 0)
		return (-1);
	if (pid == 0)
		child_wrapper(storage, cmd_node);
	else
		parent_wrapper(storage, cmd_node);
	storage->last_pid = pid;
	return (0);
}

void	child_wrapper(t_exec *storage, t_cmd *current)
{
	if (storage->pre_read_fd != -1)
	{
		dup2(storage->pre_read_fd, 0);
		close(storage->pre_read_fd);
	}
	if (current->next)
	{
		dup2(storage->pipe_fd[1], 1);
		close(storage->pipe_fd[1]);
		close(storage->pipe_fd[0]);
	}
	infile_outfile_check(storage, current);
	exec_fork(storage, current);
}

void	exec_fork(t_exec *storage, t_cmd *cmd_node)
{
	if (is_builtin(storage, cmd_node->cmd_flags[0]) == 0)
	{
		if (path_ramp(storage, cmd_node->cmd_flags) != 0)
		{
			write(2, "Command not found\n", 19);
			path_env_free(storage);
			exit(127);
		}
		execve(storage->command_path, cmd_node->cmd_flags, storage->execve_env);
		perror("exec failed");
		path_env_free(storage);
		exit(127);
	}
	else
		exit(exec_builtin(storage, cmd_node));
}

void	parent_wrapper(t_exec *storage, t_cmd *current)
{
	if (storage->pre_read_fd != -1)
		close(storage->pre_read_fd);
	if (current->next)
	{
		close(storage->pipe_fd[1]);
		storage->pre_read_fd = storage->pipe_fd[0];
	}
}

void	wait_for_child(t_exec *storage)
{
	int	status;
	int	reaped_pid;

	while ((reaped_pid = wait(&status)) > 0)
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
