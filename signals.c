/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jille <jille@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 17:11:27 by esezalor          #+#    #+#             */
/*   Updated: 2026/04/19 12:19:02 by jille            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	config_interactive_sigs(void)
{
	struct sigaction	interactive_int;
	struct sigaction	interactive_quit;

	rl_signal_event_hook = sh_readline_hook;
	// rl_event_hook = sh_readline_hook;
	ft_bzero(&interactive_int, sizeof(interactive_int));
	interactive_int.sa_handler = sh_global;
	sigemptyset(&interactive_int.sa_mask);
	interactive_int.sa_flags = 0;
	sigaction(SIGINT, &interactive_int, NULL);
	interactive_quit.sa_handler = SIG_IGN;
	interactive_quit.sa_flags = 0;
	sigemptyset(&interactive_quit.sa_mask);
	sigaction(SIGQUIT, &interactive_quit, NULL);
}

void	config_child_ign(void)
{
	struct sigaction	child_int_ign;

	child_int_ign.sa_handler = SIG_IGN;
	child_int_ign.sa_flags = 0;
	sigemptyset(&child_int_ign.sa_mask);
	sigaction(SIGINT, &child_int_ign, NULL);
}

void	config_child_dfl(void)
{
	struct sigaction	child_int_dfl;
	struct sigaction	child_quit_dfl;

	child_int_dfl.sa_handler = SIG_DFL;
	child_int_dfl.sa_flags = 0;
	sigemptyset(&child_int_dfl.sa_mask);
	sigaction(SIGINT, &child_int_dfl, NULL);
	child_quit_dfl.sa_handler = SIG_DFL;
	child_quit_dfl.sa_flags = 0;
	sigemptyset(&child_quit_dfl.sa_mask);
	sigaction(SIGQUIT, &child_quit_dfl, NULL);
}
