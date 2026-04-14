/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esezalor <esezalor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 17:31:17 by jille             #+#    #+#             */
/*   Updated: 2026/04/14 14:07:26 by esezalor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headerfiles/minishell.h"

int	check_redirection(t_type type)
{
	return (type == tk_REDIR_IN || type == tk_REDIR_OUT || type == tk_HERE_DOC
		|| type == tk_APPEND);
}

int	print_syntax_error(char *token)
{
	if (!token)
		write(2, "jeis: syntax error unexpected token `newline'\n", 47);
	else
	{
		write(2, "jeis: syntax error unexpected token ", 37);
		write(2, token, ft_strlen(token));
		write(2, "\n", 2);
	}
	return (1);
}

int	check_syntax(t_token *tokens, t_exec *storage)
{
	if (!tokens)
		return (0);
	if (tokens->type == tk_PIPE)
		return (print_syntax_error("|"), storage->exit_code = 2);
	while (tokens)
	{
		if (tokens->type == tk_PIPE)
		{
			if (!tokens->next)
				return (print_syntax_error(NULL), storage->exit_code = 2);
			if (tokens->next->type == tk_PIPE)
				return (print_syntax_error("|"), storage->exit_code = 2);
		}
		else if (check_redirection(tokens->type))
		{
			if (!tokens->next)
				return (print_syntax_error(NULL), storage->exit_code = 2);
			if (tokens->next->type != tk_WORD)
				return (print_syntax_error(tokens->next->content),
					storage->exit_code = 2);
		}
		tokens = tokens->next;
	}
	return (0);
}
