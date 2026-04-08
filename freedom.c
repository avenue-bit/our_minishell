/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freedom.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esezalor <esezalor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 14:10:43 by esezalor          #+#    #+#             */
/*   Updated: 2026/04/08 20:23:18 by esezalor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	freeing_ramp(t_exec *storage)
{
	free_in_readline(storage);
	free_out_readline(storage);
}

void	free_in_readline(t_exec *storage)
{
	if (storage->token_nodes)
	{
		clear_tokens(&storage->token_nodes);
		storage->token_nodes = NULL;
	}
	if (storage->command_nodes)
	{
		unlink_files(storage->command_nodes);
		clear_cmds(&storage->command_nodes);
		storage->command_nodes = NULL;
	}
	free(storage->c_pids);
	storage->c_pids = NULL;
	if (storage->command_path)
	{
		free(storage->command_path);
		storage->command_path = NULL;
	}
	ft_arrayfree(storage->all_paths);
	storage->all_paths = NULL;
}
void	unlink_files(t_cmd *cmds)
{
	t_cmd	*current;

	current = cmds;
	while (current)
	{
		if (current->infile && current->heredoc_delim)
		{
			if (access(current->infile, F_OK) != -1)
				unlink(current->infile);
		}
		current = current->next;
	}
}

void	free_out_readline(t_exec *storage)
{
	envclear_allnodes(&storage->environment);
	ft_arrayfree(storage->execve_env);
	failexec_close(storage);
}

void	failexec_close(t_exec *storage)
{
	if (storage->pre_read_fd >= 0)
		close(storage->pre_read_fd);
	if (storage->pipe_fd[1] >= 0)
		close(storage->pipe_fd[1]);
	if (storage->pipe_fd[0] >= 0)
		close(storage->pipe_fd[0]);
	if (storage->built_in >= 0)
		close(storage->built_in);
	if (storage->built_out >= 0)
		close(storage->built_out);
}
