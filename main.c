/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esezalor <esezalor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 19:24:33 by esezalor          #+#    #+#             */
/*   Updated: 2026/04/15 15:33:51 by esezalor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headerfiles/minishell.h"

volatile __sig_atomic_t	g_signal = 0;

void	sh_global(int signum)
{
	g_signal = signum;
}

// int	sh_readline_hook(void)
// {
// 	if(g_signal == SIGINT)
// 	{
// 		rl_replace_line("", 0);
// 		rl_done = 1;
// 	}
// 	return (0);
// }

int	sh_readline_hook(void)
{
	if (g_signal == SIGINT)
	{
		if (ioctl(STDIN_FILENO, TIOCSTI, "\n") == -1)
			perror("ioctl");
		rl_replace_line("", 0);
		return (0);
	}
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	t_token	*tokens;
	t_cmd	*cmd;
	t_exec	storage;
	char	*input;

	(void)ac;
	(void)av;
	ft_bzero(&storage, sizeof(t_exec));
	envnodes_execarray_init(&storage, envp);
	config_interactive_sigs();
	while (1)
	{
		tokens = NULL;
		cmd = NULL;
		// input = readline("#jeis$ ");
		input = mini_nextline(0);
		if (!input)
		{
			write(1, "exit\n", 5);
			storage.exit_code = 0;
			break ;
		}
		// if (*input)
		// 	add_history(input);
		if (create_tokens(input, &tokens, 0, 0) != 0)
		{
			free(input);
			continue ;
		}
		expand_variables(&tokens, &storage);
		if (check_syntax(tokens, &storage))
		{
			clear_tokens(&tokens);
			free(input);
			continue ;
		}
		create_cmd_list(&cmd, tokens, &storage);
		storage.command_nodes = cmd;
		storage.token_nodes = tokens;
		if (g_signal == SIGINT)
		{
			storage.exit_code = 130;
			g_signal = 0;
			free_in_readline(&storage);
			if (input)
				free(input);
			continue ;
		}
		exec_main(&storage);
		free_in_readline(&storage);
		free(input);
		if (storage.exit_flag == 1)
			break ;
	}
	free_out_readline(&storage);
	exit(storage.exit_code);
}
