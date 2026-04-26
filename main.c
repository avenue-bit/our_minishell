/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jille <jille@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 19:24:33 by esezalor          #+#    #+#             */
/*   Updated: 2026/04/26 15:28:19 by jille            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile __sig_atomic_t	g_signal = 0;

void	sh_global(int signum)
{
	g_signal = signum;
}

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
	t_exec	storage;
	int		status;

	(void)ac;
	(void)av;
	ft_bzero(&storage, sizeof(t_exec));
	envnodes_execarray_init(&storage, envp);
	config_interactive_sigs();
	while (1)
	{
		status = run_prompt(&storage);
		if (status == -1)
			break ;
	}
	free_out_readline(&storage);
	return (storage.exit_code);
}
