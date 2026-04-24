/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pnf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esezalor <esezalor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 14:45:59 by esezalor          #+#    #+#             */
/*   Updated: 2026/04/24 15:13:08 by esezalor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fork_ramp(t_exec *storage, t_cmd *cmd_node, int i)
{
	if (cmd_node->next)
	{
		if (pipe(storage->pipe_fd) == -1)
			return (freeing_ramp(storage), perror("pipe"), exit(1), 0);
	}
	config_child_ign();
	storage->c_pids[i] = fork();
	if (storage->c_pids[i] < 0)
		return (freeing_ramp(storage), perror("fork"), exit(1), 0);
	if (storage->c_pids[i] == 0)
		child_wrapper(storage, cmd_node);
	else
		parent_wrapper(storage, cmd_node);
	return (0);
}

void	child_wrapper(t_exec *storage, t_cmd *current)
{
	storage->is_child = 1;
	config_child_dfl();
	if (storage->pre_read_fd != -1)
	{
		if (dup2(storage->pre_read_fd, 0) == -1)
			return (freeing_ramp(storage), exit(1));
		close(storage->pre_read_fd);
		storage->pre_read_fd = -1;
	}
	if (current->next)
	{
		if (dup2(storage->pipe_fd[1], 1) == -1)
			return (freeing_ramp(storage), exit(1));
		close(storage->pipe_fd[1]);
		close(storage->pipe_fd[0]);
		storage->pipe_fd[1] = -1;
		storage->pipe_fd[0] = -1;
	}
	if (!infile_outfile_check(storage, current))
		return (freeing_ramp(storage), exit(1));
	exec_fork(storage, current);
}

void	exec_fork(t_exec *storage, t_cmd *cmd_node)
{
	if (!cmd_node->cmd_flags[0])
		return (freeing_ramp(storage), exit(0));
	if (is_builtin(storage, cmd_node->cmd_flags[0]) == 0)
	{
		if (path_ramp(storage, cmd_node->cmd_flags) > 0)
			return (freeing_ramp(storage), exit(storage->exit_code));
		execve(storage->command_path, cmd_node->cmd_flags, storage->execve_env);
		return (perror("execve"), free_out_readline(storage), exit(127));
	}
	else
	{
		storage->exit_code = exec_builtin(storage, cmd_node);
		return (free_out_readline(storage), exit(storage->exit_code));
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
