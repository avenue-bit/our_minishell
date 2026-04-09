/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esezalor <esezalor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 10:35:32 by esezalor          #+#    #+#             */
/*   Updated: 2026/04/09 10:37:16 by esezalor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "../minishell.h"

// Execution main and Initialisation
int		exec_main(t_exec *storage);
void	exec_main_init(t_exec *storage);
void	envnodes_execarray_init(t_exec *storage, char **envp);

// Pipe and Fork Functions
int		fork_ramp(t_exec *storage, t_cmd *cmd_node, int i);
void	exec_fork(t_exec *storage, t_cmd *cmd_node);
void	child_wrapper(t_exec *storage, t_cmd *current);
void	parent_wrapper(t_exec *storage, t_cmd *current);

// Wait Functions
int		wait_for_child(t_exec *storage);
void	child_status(t_exec *storage, int status);

// Redirection Functions
int		infile_outfile_check(t_exec *storage, t_cmd *cmd_node);
int		open_infile(t_exec *storage, t_cmd *cmd_node);
int		open_outfile(t_exec *storage, t_cmd *cmd_node);

#endif