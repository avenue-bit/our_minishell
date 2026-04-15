/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esezalor <esezalor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 18:01:06 by jille             #+#    #+#             */
/*   Updated: 2026/04/15 12:38:27 by esezalor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headerfiles/minishell.h"

void	expand_variables(t_token **tokens, t_exec *storage)
{
	t_token	*cur;
	char	*expanded_val;

	cur = *tokens;
	while (cur)
	{
		if (cur->prev && cur->prev->type == tk_HERE_DOC)
		{
			if (!remove_quotes(cur))
				return (freeing_ramp(storage), perror("Error"), exit(errno));
			cur = cur->next;
			continue ;
		}
		if (cur->type == tk_WORD && ft_strchr(cur->content, '$'))
		{
			expanded_val = process_expansion(cur->content, storage);
			if (!expanded_val)
				return (freeing_ramp(storage), perror("Error"), exit(errno));
			free(cur->content);
			cur->content = expanded_val;
		}
		if (!remove_quotes(cur))
			return (freeing_ramp(storage), perror("Error"), exit(errno));
		cur = cur->next;
	}
}
