/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freenclear.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esezalor <esezalor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 14:10:43 by esezalor          #+#    #+#             */
/*   Updated: 2026/03/16 14:50:43 by esezalor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	path_env_free(t_exec *storage)
{
	free(storage->command_path);
	ft_arrayfree(storage->all_paths, storage->n_paths + 1);
	ft_arrayfree(storage->execve_env, storage->n_env_variables);
	env_clearnode(&storage->environment);
}

void failexec_close(t_exec *storage)
{
	if (storage->pre_read_fd >= 0)
		close(storage->pre_read_fd);
	if (storage->pipe_fd[1] >= 0)
		close(storage->pipe_fd[1]);
	if (storage->pipe_fd[0] >= 0)
		close(storage->pipe_fd[0]);
}

void heredoc_cleanup(t_cmd *head_node)
{
	t_cmd *current;
	
	current = head_node;
	while(current)
	{
		if(current->heredoc == TRUE)
			unlink(current->infile);
		current = current->next;
	}
}