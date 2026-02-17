
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

void	clear_tokens(t_token **list)
{
	t_token	*tmp;

	if (!list || !*list)
		return ;
	while (*list)
	{
		tmp = (*list)->next;
		if ((*list)->content)
			free((*list)->content);
		free(*list);
		*list = tmp;
	}
}

int	add_token_node(t_token **list, char *content, t_type type)
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
	if (!*list)
	{
		new_node->prev = NULL;
		*list = new_node;
	}
	else
	{
		temp = *list;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new_node;
		new_node->prev = temp;
	}
	return (ft_strlen(content));
}

int	handle_words(char *input, t_token **list)
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
	if (add_token_node(list, word, tk_WORD) == -1)
		return (free(word), -1);
	return (free(word), i);
}

void	create_tokens(char *input, t_token **list, int check)
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
			check = add_token_node(list, "|", tk_PIPE);
		else if (input[i] == '<' && input[i + 1] == '<')
			check = add_token_node(list, "<<", tk_HERE_DOC);
		else if (input[i] == '>' && input[i + 1] == '>')
			check = add_token_node(list, ">>", tk_APPEND);
		else if (input[i] == '<')
			check = add_token_node(list, "<", tk_REDIR_IN);
		else if (input[i] == '>')
			check = add_token_node(list, ">", tk_REDIR_OUT);
		else
			check = handle_words(&input[i], list);
		if (check == -1)
			return (clear_tokens(list));
		i += check;
	}
}

void	print_tokens(t_token *list)
{
	while (list)
	{
		printf("Type: %d | Content: [%s]\n", list->type, list->content);
		list = list->next;
	}
}

int	count_list_words(t_token *list)
{
	t_token	*tmp;
	int		counter;

	counter = 0;
	tmp = list;
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

void	create_cmd_list(t_cmd **cmd, t_token *list)
{
	t_token	*tmp;
	int		word_num;

	if (!list)
		return ;
	word_num = count_list_words(list);
	printf("NB: %d", word_num);
	tmp = list;
	// while (tmp->next)
	// {
	// 	if (tmp->content)
	// 		{
	// 			add_cmd_node(cmd, tmp->content, tmp->type);
	// 		}
	// }
}

int	main(int ac, char **av, char **envp)
{
	t_token	*list;
	t_cmd	*cmd;

	list = NULL;
	cmd = NULL;
	printf("Input %s\n\n", av[1]);
	create_tokens(av[1], &list, 0);
	create_cmd_list(&cmd, list);
	print_tokens(list);
	clear_tokens(&list);
	return (0);
}
