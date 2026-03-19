/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_n_close.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esezalor <esezalor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 14:10:43 by esezalor          #+#    #+#             */
/*   Updated: 2026/03/19 18:21:45 by esezalor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void freeing_ramp(t_exec *storage)
{
	env_clearnode(&storage->environment);
	path_env_free(storage);
	failexec_close(storage);
}

void	path_env_free(t_exec *storage)
{
	free(storage->command_path);
	storage->command_path = NULL;
	ft_arrayfree(storage->all_paths);
	ft_arrayfree(storage->execve_env);
	clear_cmds(&storage->command_nodes);
	storage->command_nodes = NULL;
	clear_tokens(&storage->token_nodes);
	storage->token_nodes = NULL;
}

void	failexec_close(t_exec *storage)
{
	if (storage->pre_read_fd >= 0)
		close(storage->pre_read_fd);
	if (storage->pipe_fd[1] >= 0)
		close(storage->pipe_fd[1]);
	if (storage->pipe_fd[0] >= 0)
		close(storage->pipe_fd[0]);
	if(storage->built_in >= 0)
		close(storage->built_in);
	if(storage->built_out >= 0)
		close(storage->built_out);
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