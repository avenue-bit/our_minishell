/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ridiculous._parsing.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esezalor <esezalor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 14:35:30 by esezalor          #+#    #+#             */
/*   Updated: 2026/03/09 14:36:21 by esezalor         ###   ########.fr       */
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
	cmd_head = cmd_newnode(argv[1]);
	if (!cmd_head)
		return (NULL);
	cmd_head->next = NULL;
	return (cmd_head);
}

t_cmd	*cmd_newnode(char *command)
{
	t_cmd *new_cmd;

	new_cmd = malloc(sizeof(t_cmd));
	if (!new_cmd)
		return (NULL);
	new_cmd->cmd_flags = malloc(sizeof(char *) * 2);
	if (!new_cmd->cmd_flags)
		return (NULL);
	new_cmd->cmd_flags[0] = command;
	new_cmd->cmd_flags[1] = NULL;
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