
#include "minishell.h"

int		heredoc_to_file(t_cmd **cmd);

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
		if ((*node)->infile && ft_strncmp((*node)->infile, "._#", 3) != 0)
			free((*node)->infile);
		if ((*node)->outfile)
			free((*node)->outfile);
		if ((*node)->heredoc_delim)
			free((*node)->heredoc_delim);
		free(*node);
		*node = tmp;
	}
}

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

int	create_tokens(char *input, t_token **tokens, int check, int i)
{
	while (input[i])
	{
		while (input[i] && (input[i] == ' ' || input[i] >= 9 && input[i] <= 13))
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

int	process_heredoc(t_token *tokens, t_cmd *cmd)
{
	free(cmd->heredoc_delim),
		cmd->heredoc_delim = ft_strdup(tokens->content);
	if (!cmd->heredoc_delim)
		return (errno);
	heredoc_to_file(&cmd);
	return (0);
}

int	fill_cmd_data_redir(t_token **tokens, t_cmd *cmd)
{
	t_type	type;
	int		fd;

	type = (*tokens)->type;
	*tokens = (*tokens)->next;
	if (!*tokens)
		return (ENOMEM);
	errno = 0;
	if (type == tk_HERE_DOC)
		return (process_heredoc(*tokens, cmd));
	if (type == tk_REDIR_IN)
		fd = open((*tokens)->content, O_RDONLY);
	else if (type == tk_APPEND)
		fd = open((*tokens)->content, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open((*tokens)->content, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (perror((*tokens)->content), ENOENT);
	close(fd);
	errno = 0;
	return (set_redir_path(cmd, tokens, type));
	return (0);
}

int	fill_node_data(t_token **tokens, t_cmd *cmd, int *i)
{
	int	reint;

	if ((*tokens)->type == tk_WORD)
	{
		cmd->cmd_flags[*i] = ft_strdup((*tokens)->content);
		if (!cmd->cmd_flags[(*i)++])
			return (ENOMEM);
	}
	else if ((*tokens)->type >= tk_REDIR_IN && (*tokens)->type <= tk_APPEND)
	{
		reint = fill_cmd_data_redir(tokens, cmd);
		if (reint != 0)
			return (reint);
	}
	return (0);
}

int	fill_cmd_data(t_token **tokens, t_cmd *cmd)
{
	int	i;
	int	reint;

	i = 0;
	while (*tokens && (*tokens)->type != tk_PIPE)
	{
		reint = fill_node_data(tokens, cmd, &i);
		if (reint == ENOMEM)
			return (perror("Error"), ENOMEM);
		if (reint == ENOENT)
		{
			while (*tokens && (*tokens)->type != tk_PIPE)
				*tokens = (*tokens)->next;
			return (ENOENT);
		}
		if (*tokens)
			*tokens = (*tokens)->next;
	}
	return (0);
}

t_cmd	*init_new_cmd(t_cmd **cmd_list, t_token *tokens)
{
	t_cmd	*current_cmd;

	current_cmd = add_cmd_node(cmd_list);
	if (!current_cmd)
		return (NULL);
	current_cmd->cmd_flags = ft_calloc((count_tokens_words(tokens) + 1),
			sizeof(char *));
	if (!current_cmd->cmd_flags)
		return (NULL);
	return (current_cmd);
}

void	create_cmd_list(t_cmd **cmd_list, t_token *tokens)
{
	t_token	*tmp;
	int		reint;
	t_cmd	*current_cmd;

	if (!tokens)
		return ;
	tmp = tokens;
	while (tmp)
	{
		current_cmd = init_new_cmd(cmd_list, tmp);
		if (!current_cmd)
			return (clear_tokens(&tokens), clear_cmds(cmd_list),
				perror("Error"), exit(errno));
		reint = fill_cmd_data(&tmp, current_cmd);
		if (reint == ENOMEM)
			return (clear_tokens(&tokens), clear_cmds(cmd_list), exit(errno));
		if (reint == ENOENT)
			remove_last_cmd_node(cmd_list, current_cmd);
		if (tmp && tmp->type == tk_PIPE)
			tmp = tmp->next;
	}
}

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

int	check_syntax(t_token *tokens)
{
	if (!tokens)
		return (0);
	if (tokens->type == tk_PIPE)
		return (print_syntax_error("|"));
	while (tokens)
	{
		if (tokens->type == tk_PIPE)
		{
			if (!tokens->next)
				return (print_syntax_error(NULL));
			if (tokens->next->type == tk_PIPE)
				return (print_syntax_error("|"));
		}
		else if (check_redirection(tokens->type))
		{
			if (!tokens->next)
				return (print_syntax_error(NULL));
			if (tokens->next->type != tk_WORD)
				return (print_syntax_error(tokens->next->content));
		}
		tokens = tokens->next;
	}
	return (0);
}

char	*create_heredoc_file_name(int num)
{
	static char	name[20];
	int			temp;
	int			len;

	temp = num;
	len = 0;
	name[0] = '.';
	name[1] = '_';
	name[2] = '#';
	temp = num;
	len = (num == 0);
	while (temp > 0 && ++len)
		temp /= 10;
	name[len + 3] = '\0';
	temp = num;
	while (len > 0)
	{
		name[len + 2] = (temp % 10) + '0';
		temp /= 10;
		len--;
	}
	if (num == 0)
		name[3] = '0';
	return (name);
}

void heredoc_loop(t_cmd **cmd, int h_fd)
{
	char		*line;
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			write(2, "jeis: warning: here-document delimited by end-of-file (wanted `", 64);
			write(2, (*cmd)->heredoc_delim, strlen((*cmd)->heredoc_delim));
			write(2, "')\n", 3);
			break ;
		}
		if (ft_strncmp(line, (*cmd)->heredoc_delim,
				ft_strlen((*cmd)->heredoc_delim)) == 0)
		{
			free(line);
			break ;
		}
		write(h_fd, line, ft_strlen(line));
		write(h_fd, "\n", 1);
		free(line);
	}
}

int	heredoc_to_file(t_cmd **cmd)
{
	int			fd;
	char		*filename;
	static int	h_num;

	if (!(*cmd)->heredoc_delim)
		return (print_syntax_error(NULL));
	filename = create_heredoc_file_name(h_num++);
	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		return (perror("heredoc hiddenfile open"), ENOENT);
	heredoc_loop(cmd, fd);
	close(fd);
	(*cmd)->infile = filename;
	return (0);
}

void	print_tokens(t_token *tokens)
{
	while (tokens)
	{
		printf("Type: %d | Content: [%s]\n", tokens->type, tokens->content);
		tokens = tokens->next;
	}
	printf("\n\n");
}

void	print_cmd_list(t_cmd *cmd)
{
	int	i;
	int	cmd_num;

	cmd_num = 0;
	while (cmd)
	{
		printf("--- COMMAND %d ---\n", cmd_num++);
		printf("Infile: [%s]\n", cmd->infile);
		printf("Outfile: [%s] (Append: %d)\n", cmd->outfile, cmd->append);
		printf("Heredoc delim: [%s]\n", cmd->heredoc_delim);
		printf("Commands & Flags:   ");
		i = 0;
		if (cmd->cmd_flags)
		{
			while (cmd->cmd_flags[i])
				printf("[%s]", cmd->cmd_flags[i++]);
		}
		printf("\n\n");
		cmd = cmd->next;
	}
}

int	main(int ac, char **av, char **envp)
{
	t_token	*tokens;
	t_cmd	*cmd;
	char	*input;

	/*  ----Check without readline---- */
	/*tokens = NULL;
	cmd = NULL;
	printf("Input %s\n\n", av[1]);
	create_tokens(av[1], &tokens, 0, 0);
	check_syntax(tokens);
	create_cmd_list(&cmd, tokens);
	print_tokens(tokens);
	print_cmd_list(cmd);
	printf("%s\n", create_heredoc_file_name(5));
	// exec_main(ac, av, envp, cmd);
	if (tokens)
		clear_tokens(&tokens);
	if (cmd)
		clear_cmds(&cmd);
	return (0); */
	/*  ----END--- */
	/* ----Check with readline----*/
	(void)ac;
	(void)av;
	(void)envp;
	while (1)
	{
		tokens = NULL;
		cmd = NULL;
		input = readline("#jeis$ ");
		if (!input)
		{
			write(1, "exiting...\n", 12);
			break ;
		}
		if (ft_strncmp(input, "exit", 5) == 0)
		{
			clear_tokens(&tokens);
			clear_cmds(&cmd);
			exit(errno);
		}
		if (*input)
			add_history(input);
		if (create_tokens(input, &tokens, 0, 0) != 0)
		{
			free(input);
			continue ;
		}
		if (check_syntax(tokens))
		{
			clear_tokens(&tokens);
			free(input);
			continue ;
		}
		create_cmd_list(&cmd, tokens);
		// exec_main(ac, av, envp, cmd);
		//print_tokens(tokens);
		//print_cmd_list(cmd);
		if (tokens)
			clear_tokens(&tokens);
		if (cmd)
			clear_cmds(&cmd);
		free(input);
	}
}
