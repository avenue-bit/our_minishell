/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clearing_tkcmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jille <jille@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 17:31:17 by jille             #+#    #+#             */
/*   Updated: 2026/04/19 12:18:11 by jille            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_tokens(t_token **tokens)
{
	t_token	*tmp;

	if (!tokens || !*tokens)
		return ;
	while (*tokens)
	{
		tmp = (*tokens)->next;
		if ((*tokens)->content)
			free((*tokens)->content);
		free(*tokens);
		*tokens = tmp;
	}
}

void	clear_cmds(t_cmd **node)
{
	t_cmd	*tmp;
	int		i;

	while (*node)
	{
		tmp = (*node)->next;
		if ((*node)->cmd_flags)
		{
			i = 0;
			while ((*node)->cmd_flags[i])
				free((*node)->cmd_flags[i++]);
			free((*node)->cmd_flags);
		}
		if ((*node)->infile)
			free((*node)->infile);
		if ((*node)->outfile)
			free((*node)->outfile);
		if ((*node)->heredoc_delim)
			free((*node)->heredoc_delim);
		free(*node);
		*node = tmp;
	}
}
