/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jille <jille@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 17:31:17 by jille             #+#    #+#             */
/*   Updated: 2026/04/10 17:51:09 by jille            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headerfiles/minishell.h"

int	add_token_node(t_token **tokens, char *content, t_type type)
{
	t_token	*new_node;
	t_token	*temp;

	new_node = ft_calloc(1, sizeof(t_token));
	if (!new_node)
		return (-1);
	new_node->content = ft_strdup(content);
	if (!new_node->content)
		return (free(new_node), -1);
	new_node->type = type;
	new_node->next = NULL;
	if (!*tokens)
	{
		new_node->prev = NULL;
		*tokens = new_node;
	}
	else
	{
		temp = *tokens;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new_node;
		new_node->prev = temp;
	}
	return (ft_strlen(content));
}

int	handle_words(char *input, t_token **tokens)
{
	int		i;
	char	quotingmark;
	char	*word;

	i = 0;
	quotingmark = 0;
	while (input[i])
	{
		if ((input[i] == '\'' || input[i] == '\"') && quotingmark == 0)
			quotingmark = input[i];
		else if (input[i] == quotingmark)
			quotingmark = 0;
		if (quotingmark == 0 && (input[i] == ' ' || input[i] == '|'
				|| input[i] == '<' || input[i] == '>'))
			break ;
		i++;
	}
	if (quotingmark)
		return (write(2, "Error: \" / \' missing\n", 22), -2);
	word = ft_substr(input, 0, i);
	if (!word)
		return (-1);
	if (add_token_node(tokens, word, tk_WORD) == -1)
		return (free(word), -1);
	return (free(word), i);
}

int	create_tokens(char *inp, t_token **tokens, int check, int i)
{
	while (inp[i])
	{
		while (inp[i] && (inp[i] == ' ' || (inp[i] >= 9 && inp[i] <= 13)))
			i++;
		if (!inp[i])
			break ;
		if (inp[i] == '|')
			check = add_token_node(tokens, "|", tk_PIPE);
		else if (inp[i] == '<' && inp[i + 1] == '<')
			check = add_token_node(tokens, "<<", tk_HERE_DOC);
		else if (inp[i] == '>' && inp[i + 1] == '>')
			check = add_token_node(tokens, ">>", tk_APPEND);
		else if (inp[i] == '<')
			check = add_token_node(tokens, "<", tk_REDIR_IN);
		else if (inp[i] == '>')
			check = add_token_node(tokens, ">", tk_REDIR_OUT);
		else
			check = handle_words(&inp[i], tokens);
		if (check == -1)
			return (clear_tokens(tokens), perror("Error"), exit(errno), 1);
		if (check == -2)
			return (clear_tokens(tokens), 2);
		i += check;
	}
	return (0);
}

int	count_tokens_words(t_token *tokens)
{
	t_token	*tmp;
	int		counter;

	counter = 0;
	tmp = tokens;
	while (tmp)
	{
		if (tmp->type == tk_PIPE)
			break ;
		if (tmp->type == tk_WORD)
			counter++;
		tmp = tmp->next;
	}
	return (counter);
}
