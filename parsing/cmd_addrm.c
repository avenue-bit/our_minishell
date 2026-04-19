/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_addrm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jille <jille@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 17:31:17 by jille             #+#    #+#             */
/*   Updated: 2026/04/19 12:18:14 by jille            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*add_cmd_node(t_cmd **cmd_list)
{
	t_cmd	*new_node;
	t_cmd	*last;

	new_node = ft_calloc(1, sizeof(t_cmd));
	if (!new_node)
		return (NULL);
	new_node->next = NULL;
	if (!*cmd_list)
	{
		new_node->prev = NULL;
		new_node->next = NULL;
		*cmd_list = new_node;
		return (new_node);
	}
	last = *cmd_list;
	while (last->next)
		last = last->next;
	last->next = new_node;
	new_node->prev = last;
	return (new_node);
}

void	remove_last_cmd_node(t_cmd **cmd_list, t_cmd *node)
{
	int	i;

	if (node->prev)
		node->prev->next = NULL;
	else
		*cmd_list = NULL;
	if (node->cmd_flags)
	{
		i = 0;
		while (node->cmd_flags[i])
			free(node->cmd_flags[i++]);
		free(node->cmd_flags);
	}
	if (node->infile)
		free(node->infile);
	if (node->outfile)
		free(node->outfile);
	free(node);
}

int	set_redir_path(t_cmd *cmd, t_token **tokens, t_type type)
{
	if (type == tk_REDIR_IN)
		return (free(cmd->infile), cmd->infile = ft_strdup((*tokens)->content),
			errno);
	else
		return (free(cmd->outfile), cmd->append = (type == tk_APPEND),
			cmd->outfile = ft_strdup((*tokens)->content), errno);
}
