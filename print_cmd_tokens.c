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