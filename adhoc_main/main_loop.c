/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jille <jille@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 18:56:09 by jille             #+#    #+#             */
/*   Updated: 2026/04/24 14:26:55 by jille            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_input(char **input)
{
	*input = readline("#jeis$ ");
	if (!*input)
	{
		if (isatty(STDIN_FILENO))
			write(1, "exit\n", 5);
		return (-1);
	}
	if (**input)
		add_history(*input);
	return (1);
}

int	parse_input(char *input, t_token **tokens, t_exec *storage)
{
	int	status;

	status = create_tokens(input, tokens, 0, 0);
	if (status == ENOMEM)
		return (free(input), perror("Error"), storage->exit_code = 1, -1);
	if (status != 0)
		return (free(input), storage->exit_code = status, 0);
	if (!*tokens)
		return (free(input), 0);
	status = expand_variables(tokens, storage);
	if (status != 0)
		return (clear_tokens(tokens), free(input), perror("Error"),
			storage->exit_code = 1, -1);
	if (!*tokens)
		return (free(input), 0);
	if (check_syntax(*tokens, storage))
		return (clear_tokens(tokens), free(input), 0);
	return (1);
}

int	build_commands(char *input, t_token **tokens, t_cmd **cmd, t_exec *storage)
{
	int	status;

	status = create_cmd_list(cmd, *tokens, storage);
	storage->command_nodes = *cmd;
	storage->token_nodes = *tokens;
	if (status == ENOMEM)
		return (free(input), perror("Error"), free_in_readline(storage),
			storage->exit_code = 1, -1);
	if (status == ENOENT)
		return (free(input), free_in_readline(storage), storage->exit_code = 1,
			0);
	if (status == EINTR || g_signal == SIGINT)
		return (free(input), storage->exit_code = 130, g_signal = 0,
			free_in_readline(storage), 0);
	return (1);
}

int	run_prompt(t_exec *storage)
{
	t_token	*tokens;
	t_cmd	*cmd;
	char	*input;
	int		status;

	tokens = NULL;
	cmd = NULL;
	status = get_input(&input);
	if (status != 1)
		return (status);
	status = parse_input(input, &tokens, storage);
	if (status != 1)
		return (status);
	status = build_commands(input, &tokens, &cmd, storage);
	if (status != 1)
		return (status);
	exec_main(storage);
	free_in_readline(storage);
	free(input);
	if (storage->exit_flag == 1)
		return (-1);
	return (1);
}
