
#include "minishell.h"

char	*ft_strdup(const char *s)
{
	int		i;
	char	*new_string;

	i = 0;
	while (s[i])
		i++;
	new_string = malloc(sizeof(char) * (i + 1));
	if (new_string == NULL)
		return (NULL);
	i = 0;
	while (*s)
	{
		new_string[i++] = *s;
		s++;
	}
	new_string[i] = '\0';
	return (new_string);
}

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (*(str + i) != '\0')
	{
		i++;
	}
	return (i);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	size_t	i;

	i = 0;
	if (nmemb == 0 || size == 0)
		return (malloc(0));
	if (nmemb > ((size_t)-1) / size)
		return (NULL);
	ptr = malloc(nmemb * size);
	if (ptr == NULL)
		return (NULL);
	while (i < nmemb * size)
		((unsigned char *)ptr)[i++] = 0;
	return (ptr);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	i;

	i = 0;
	if (!s || (unsigned int)ft_strlen(s) <= start)
		return (ft_calloc(1, 1));
	while (s[start + i] != '\0' && i < len)
		i++;
	substr = malloc(sizeof(char) * i + 1);
	if (!substr)
		return (NULL);
	i = 0;
	while (s[start + i] != '\0' && i < len)
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[i] = '\0';
	if ((unsigned int)ft_strlen(s) <= start)
		substr[0] = '\0';
	return (substr);
}

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

int	add_token_node(t_token **tokens, char *content, t_type type)
{
	t_token	*new_node;
	t_token	*temp;

	new_node = malloc(sizeof(t_token));
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
		return (errno = 1, perror("Error: \" / \' missing"), exit(errno), 0);
	word = ft_substr(input, 0, i);
	if (!word)
		return (-1);
	if (add_token_node(tokens, word, tk_WORD) == -1)
		return (free(word), -1);
	return (free(word), i);
}

void	create_tokens(char *input, t_token **tokens, int check)
{
	int	i;

	i = 0;
	while (input[i])
	{
		while (input[i] && (input[i] == ' ' || input[i] >= 0 && input[i] <= 13))
			i++;
		if (!input[i])
			break ;
		if (input[i] == '|')
			check = add_token_node(tokens, "|", tk_PIPE);
		else if (input[i] == '<' && input[i + 1] == '<')
			check = add_token_node(tokens, "<<", tk_HERE_DOC);
		else if (input[i] == '>' && input[i + 1] == '>')
			check = add_token_node(tokens, ">>", tk_APPEND);
		else if (input[i] == '<')
			check = add_token_node(tokens, "<", tk_REDIR_IN);
		else if (input[i] == '>')
			check = add_token_node(tokens, ">", tk_REDIR_OUT);
		else
			check = handle_words(&input[i], tokens);
		if (check == -1)
			return (clear_tokens(tokens));
		i += check;
	}
}

void	print_tokens(t_token *tokens)
{
	while (tokens)
	{
		printf("Type: %d | Content: [%s]\n", tokens->type, tokens->content);
		tokens = tokens->next;
	}
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

void	create_cmd_list(t_cmd **cmd, t_token *tokens)
{
	t_token	*tmp;
	int		word_count;
	t_cmd	*new_cmd;

	if (!tokens)
		return ;
	tmp = tokens;
	word_count = count_tokens_words(tokens);
	printf("NB: %d\n\n", word_count);
	while (tmp)
	{
		new_cmd = malloc(sizeof(t_cmd) * 1);
		if (!new_cmd)
			return (perror("Malloc fail"));
		word_count = count_tokens_words(tokens);
		new_cmd->cmd_flags = malloc(sizeof(char *) * (word_count + 1));
		if (!new_cmd->cmd_flags)
			return (free(new_cmd), perror("Malloc fail"));
		
		if (tmp->content)
		{
			//add_cmd_node(cmd, tmp->content, tmp->type);
		}
		tmp = tmp->next;
	}
}

int	main(int ac, char **av, char **envp)
{
	t_token	*tokens;
	t_cmd	*cmd;

	tokens = NULL;
	cmd = NULL;
	printf("Input %s\n\n", av[1]);
	create_tokens(av[1], &tokens, 0);
	create_cmd_list(&cmd, tokens);
	print_tokens(tokens);
	clear_tokens(&tokens);
	return (0);
}


