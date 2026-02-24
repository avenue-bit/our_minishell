/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esezalor <esezalor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 17:20:11 by esezalor          #+#    #+#             */
/*   Updated: 2026/02/24 18:00:39 by esezalor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redir_close(int *fd)
{
	if (*fd > 2)
	{
		close(*fd);
		*fd = -1;
	}
}

int	redir_cleanup(t_cmd *command)
{
	redir_close(&command->fd_in);
	redir_close(&command->fd_out);
	return (-1);
}

int	cmd_init(t_cmd *commands)
{
	t_redir	*current;

	current = commands->redirect;
	while (current)
	{
		if (current->type == tk_REDIR_OUT)
		{
			redir_close(&commands->fd_out);
			commands->fd_out = open(current->filename,
					O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (commands->fd_out == -1)
				return (redir_cleanup(commands));
		}
		else if (current->type == tk_REDIR_IN)
		{
			redir_close(&commands->fd_in);
			commands->fd_in = open(current->filename, O_RDONLY);
			if (commands->fd_in == -1)
				return (redir_cleanup(commands));
		}
		current = current->next;
	}
	return (0);
}

int childsplay(t_cmd *commands, char **environment)
{
	
	if (commands->fd_in != -1)
	{
		dup2(commands->fd_in, STDIN_FILENO);
		close(commands->fd_in);
	}
	if (commands->fd_out != -1)
	{
		dup2(commands->fd_out, STDOUT_FILENO);
		close(commands->fd_out); // inefficient will change this
	}
	execve(commands->cmnd_flags[0], commands->cmnd_flags, environ);
	return(perror("execve"), -1);
}

int	redirecting(t_cmd *commands, char **environ)
{
	pid_t	pid;
	int		status;
	int		child_pid;

	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		if(childsplay(commands, environ) == -1)
			exit(127);
	}
	else
	{
		child_pid = waitpid(pid, &status, WNOHANG);
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_cmd commands;

	ft_bzero(&commands, sizeof(t_cmd));
	commands.fd_in = -1;
	commands.fd_out = -1;
	if (cmd_init(&commands) == -1)
		return (perror("open failed"), -1); // placeholder
	redirecting(&commands, envp);
	return (0);
}