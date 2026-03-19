/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_n_close.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esezalor <esezalor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 14:10:43 by esezalor          #+#    #+#             */
/*   Updated: 2026/03/19 16:09:03 by esezalor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	path_env_free(t_exec *storage)
{
	free(storage->command_path);
	storage->command_path = NULL;
	ft_arrayfree(storage->all_paths, storage->n_paths);
	storage->all_paths = NULL;
	ft_arrayfree(storage->execve_env, storage->n_env_variables);
	storage->execve_env = NULL;
	env_clearnode(&storage->environment);
	storage->environment = NULL;
}

void	failexec_close(t_exec *storage)
{
	if (storage->pre_read_fd >= 0)
		close(storage->pre_read_fd);
	if (storage->pipe_fd[1] >= 0)
		close(storage->pipe_fd[1]);
	if (storage->pipe_fd[0] >= 0)
		close(storage->pipe_fd[0]);
}

// void heredoc_cleanup(t_cmd *head_node)
// {
// 	t_cmd *current;

// 	current = head_node;
// 	while(current)
// 	{
// 		if(current->heredoc == TRUE)
// 			unlink(current->infile);
// 		current = current->next;
// 	}
// }