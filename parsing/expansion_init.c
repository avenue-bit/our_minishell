/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jille <jille@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 18:01:06 by jille             #+#    #+#             */
/*   Updated: 2026/04/19 12:20:23 by jille            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int expand_word_token(t_token *cur, t_exec *storage)
{
	char *expanded_val;

	if ((cur->type != tk_WORD) || !ft_strchr(cur->content, '$'))
		return (0);
	expanded_val = process_expansion(cur->content, storage);
	if (!expanded_val)
		return (-1);
	free(cur->content);
	cur->content = expanded_val;
	return (0);
}

int	expand_variables(t_token **tokens, t_exec *storage)
{
	t_token	*cur;

	cur = *tokens;
	while (cur)
	{
		if (cur->prev && cur->prev->type == tk_HERE_DOC)
		{
			if (!remove_quotes(cur))
				return (-1);
		}
		else 
		{
			if (expand_word_token(cur, storage) == -1)
				return (-1);
			if (!remove_quotes(cur))
				return (-1);
		}
		cur = cur->next;
	}
	return (0);
}
