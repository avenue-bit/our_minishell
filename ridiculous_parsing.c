/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ridiculous_parsing.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esezalor <esezalor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 14:35:30 by esezalor          #+#    #+#             */
/*   Updated: 2026/03/13 17:50:21 by esezalor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//********************************************************//
// THIS IS FOR TESTING PURPOSES WHILE JOSH FINISHES WORK
//********************************************************//

t_cmd	*cmdnodes_init(char **argv)
{
	t_cmd	*cmd_head;

	cmd_head = NULL;
	cmd_head = cmd_newnode(argv);
	if (!cmd_head)
		return (NULL);
	cmd_head->next = NULL;
	return (cmd_head);
}

t_cmd	*cmd_newnode(char **command)
{
	t_cmd *new_cmd;

	new_cmd = malloc(sizeof(t_cmd));
	if (!new_cmd)
		return (NULL);
	new_cmd->cmd_flags = malloc(sizeof(char *) * 3);
	if (!new_cmd->cmd_flags)
		return (NULL);
	new_cmd->infile = "test_in.txt";
	new_cmd->outfile = "test_out.txt";
	new_cmd->cmd_flags[0] = command[1];
	new_cmd->cmd_flags[1] = command[2];
	new_cmd->cmd_flags[2] = NULL;
	new_cmd->next = NULL;
	return (new_cmd);
}

void	cmd_clearnode(t_cmd **cmd_lst)
{
	t_cmd	*current_node;
	t_cmd	*next_node;

	if (!*cmd_lst)
		return ;
	current_node = *cmd_lst;
	while (current_node)
	{
		next_node = current_node->next;
		free(current_node);
		current_node = next_node;
	}
	*cmd_lst = NULL;
}
//********************************************************//
// THIS IS FOR TESTING PURPOSES WHILE JOSH FINISHES WORK
//********************************************************//