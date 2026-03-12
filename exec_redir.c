/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esezalor <esezalor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 15:15:54 by esezalor          #+#    #+#             */
/*   Updated: 2026/03/12 15:54:54 by esezalor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	infile_outfile_check(t_exec *storage, t_cmd *cmd_node)
{
	storage->infile_fd = -2;
	storage->outfile_fd = -2;
	if (cmd_node->infile)
		open_infile(storage, cmd_node);
	if (cmd_node->outfile)
		open_outfile(storage, cmd_node);
}

void	open_infile(t_exec *storage, t_cmd *cmd_node)
{
	storage->infile_fd = open(cmd_node->infile, O_RDONLY);
	if (storage->infile_fd == -1)
	{
		write(2, "Failed open\n", 12);
		failexec_close(storage);
		path_env_free(storage);
		exit(1);
	}
	dup2(storage->infile_fd, 0);
	close(storage->infile_fd);
}

void	open_outfile(t_exec *storage, t_cmd *cmd_node)
{
	if (cmd_node->append == TRUE)
		storage->outfile_fd = open(cmd_node->outfile,
				O_CREAT | O_WRONLY | O_APPEND, 0644);
	else
		storage->outfile_fd = open(cmd_node->outfile,
				O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (storage->outfile_fd == -1)
	{
		write(2, "Failed open\n", 12);
		failexec_close(storage);
		path_env_free(storage);
		exit(1);
	}
	dup2(storage->outfile_fd, 1);
	close(storage->outfile_fd);
}
