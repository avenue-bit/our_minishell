/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esezalor <esezalor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 15:15:54 by esezalor          #+#    #+#             */
/*   Updated: 2026/03/18 14:13:22 by esezalor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	infile_outfile_check(t_exec *storage, t_cmd *cmd_node)
{
	storage->infile_fd = -2;
	storage->outfile_fd = -2;
	if (cmd_node->infile)
	{
		if (!open_infile(storage, cmd_node))
			return (write(2, "Failed open\n", 12), 0);
	}
	if (cmd_node->outfile)
	{
		if (!open_outfile(storage, cmd_node))
			return (write(2, "Failed open\n", 12), 0);
	}
	return (1);
}

int	open_infile(t_exec *storage, t_cmd *cmd_node)
{
	storage->infile_fd = open(cmd_node->infile, O_RDONLY);
	if (storage->infile_fd == -1)
		return (0); // Error handling needed
	dup2(storage->infile_fd, 0);
	close(storage->infile_fd);
	return (1);
}

int	open_outfile(t_exec *storage, t_cmd *cmd_node)
{
	if (cmd_node->append == TRUE)
		storage->outfile_fd = open(cmd_node->outfile,
				O_CREAT | O_WRONLY | O_APPEND, 0644);
	else
		storage->outfile_fd = open(cmd_node->outfile,
				O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (storage->outfile_fd == -1)
		return (0);
	dup2(storage->outfile_fd, 1);
	close(storage->outfile_fd);
	return (1);
}
