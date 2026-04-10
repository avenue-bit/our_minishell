/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_functions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jille <jille@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 18:06:40 by jille             #+#    #+#             */
/*   Updated: 2026/04/10 18:49:33 by jille            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headerfiles/minishell.h"

char	*append_and_advance(char *str, char c, int *i)
{
	str = append_char(str, c);
	if (!str)
		return (NULL);
	(*i)++;
	return (str);
}

char	*handle_dollar_case(char *str, char *input, t_exec *storage, int *i)
{
	if (input[*i + 1] == '?')
		str = handle_exit_code(str, storage->exit_code, i);
	else if (ft_isalpha(input[*i + 1]) || input[*i + 1] == '_')
		str = handle_variable(str, input, storage->environment, i);
	else if (ft_isdigit(input[*i + 1]))
		*i += 2;
	else
		str = append_and_advance(str, input[*i], i);
	return (str);
}

char	*handle_quote_case(char *str, char *input, int *i, char *quote)
{
	if ((input[*i] == '\'' || input[*i] == '\"') && *quote == 0)
		*quote = input[*i];
	else if (input[*i] == *quote)
		*quote = 0;
	return (append_and_advance(str, input[*i], i));
}

char	*process_expansion(char *input, t_exec *storage)
{
	char	*new_str;
	int		i;
	char	quote;

	i = 0;
	quote = 0;
	new_str = ft_strdup("");
	if (!new_str)
		return (NULL);
	while (input[i])
	{
		if (((input[i] == '\'' || input[i] == '\"') && quote == 0)
			|| input[i] == quote)
			new_str = handle_quote_case(new_str, input, &i, &quote);
		else if (input[i] == '$' && quote != '\'')
			new_str = handle_dollar_case(new_str, input, storage, &i);
		else
			new_str = append_and_advance(new_str, input[i], &i);
		if (!new_str)
			return (NULL);
	}
	return (new_str);
}

char	*remove_quotes(t_token *tokens)
{
	char	*dst;
	int		i;
	int		j;
	char	quote;

	dst = malloc(ft_strlen(tokens->content) + 1);
	if (!dst)
		return (NULL);
	i = 0;
	j = 0;
	quote = 0;
	while (tokens->content[i])
	{
		if ((tokens->content[i] == '\'' || tokens->content[i] == '\"')
			&& quote == 0)
			quote = tokens->content[i++];
		else if (tokens->content[i] == quote)
		{
			quote = 0;
			i++;
		}
		else
			dst[j++] = tokens->content[i++];
	}
	return (free(tokens->content), dst[j] = '\0', tokens->content = dst, "");
}
