/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_wait.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esezalor <esezalor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 17:37:44 by esezalor          #+#    #+#             */
/*   Updated: 2026/04/07 17:50:40 by esezalor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


int	wait_for_child(t_exec *storage)
{
	int	i;
	int	status;
	int	reaped_pid;

	i = 0;
	while (i < storage->n_commands_nodes)
	{
		reaped_pid = waitpid(storage->c_pids[i], &status, 0);
		if (reaped_pid < 0)
		{
			if (errno == EINTR)
				continue ;
			else
				return (1);
		}
		if (reaped_pid > 0)
            child_status(storage, status);
		i++;
	}
	config_interactive_sigs();
	return (0);
}

void child_status(t_exec *storage, int status)
{
    if (WIFEXITED(status))
		storage->exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
    {
		storage->exit_code = 128 + WTERMSIG(status);
        if(WTERMSIG(status) == SIGINT)
            write(2, "\n", 1);
        else if(WTERMSIG(status) == SIGQUIT)
            write(2, "Quit (core dumped)\n", 19);
    }
}
    