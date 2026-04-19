/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jille <jille@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 12:24:20 by jille             #+#    #+#             */
/*   Updated: 2026/04/19 14:57:54 by jille            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			return (1);
		i++;
	}
	return (0);
}

char	*strip_quotes_str(char *str)
{
	char	*dst;
	int		i;
	int		j;
	char	quote;

	dst = malloc(ft_strlen(str) + 1);
	if (!dst)
		return (NULL);
	i = 0;
	j = 0;
	quote = 0;
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '\"') && quote == 0)
			quote = str[i++];
		else if (str[i] == quote)
		{
			quote = 0;
			i++;
		}
		else
			dst[j++] = str[i++];
	}
	return (dst[j] = '\0', str = dst);
}

char *expand_heredoc_line(char *input, t_exec *storage)
{
    char *new_str;
    int i;

    new_str = ft_strdup("");
    if (!new_str)
        return (NULL);
    i = 0;
    while (input[i])
    {
        if (input[i] == '$')
            new_str = handle_dollar_case(new_str, input, storage, &i);
        else 
            new_str = append_and_advance(new_str, input[i], &i);
        if (!new_str)
            return (NULL);
    }
    return (new_str);
}


