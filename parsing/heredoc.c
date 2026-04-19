/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jille <jille@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 17:56:59 by jille             #+#    #+#             */
/*   Updated: 2026/04/19 15:19:14 by jille            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	process_heredoc(t_token *tokens, t_cmd *cmd, t_exec *storage)
{
	free(cmd->heredoc_delim);
	cmd->heredoc_expand = !check_quotes(tokens->content);
	cmd->heredoc_delim = strip_quotes_str(tokens->content);
	if (!cmd->heredoc_delim)
		return (errno);
	return (heredoc_to_file(&cmd, storage));
}

char	*create_heredoc_file_name(int num)
{
	static char	name[20];
	int			temp;
	int			len;

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

int	heredoc_loop(t_cmd **cmd, int h_fd, t_exec *storage)
{
	char	*line;
	char	*expanded;

	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			write(2, "jeis: warning: h-doc delimited by end-of-file (wanted `",
				56);
			write(2, (*cmd)->heredoc_delim, strlen((*cmd)->heredoc_delim));
			write(2, "')\n", 3);
			return (0);
		}
		if (g_signal == SIGINT)
			return (free(line), EINTR);
		if (ft_strncmp(line, (*cmd)->heredoc_delim,
				(ft_strlen((*cmd)->heredoc_delim) + 1)) == 0)
			return (free(line), 0);
		if ((*cmd)->heredoc_expand)
		{
			expanded = expand_heredoc_line(line, storage);
			free(line);
			if (!expanded)
				return (errno);
			write(h_fd, expanded, ft_strlen(expanded));
			free(expanded);
		}
		else
		{
			write(h_fd, line, ft_strlen(line));
			free(line);
		}
		write(h_fd, "\n", 1);
	}
}

int	heredoc_to_file(t_cmd **cmd, t_exec *storage)
{
	int			fd;
	int			status;
	char		*filename;
	static int	h_num;

	if (h_num > 0)
		if ((*cmd)->infile)
			if (access((*cmd)->infile, F_OK) != -1)
				unlink((*cmd)->infile);
	if (!(*cmd)->heredoc_delim)
		return (print_syntax_error(NULL));
	filename = create_heredoc_file_name(h_num++);
	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		return (perror("heredoc hiddenfile open"), ENOENT);
	status = heredoc_loop(cmd, fd, storage);

	if (status != 0)
	{
		close(fd);
		if (access(filename, F_OK) != -1)
			unlink(filename);
		return (status);
	}
	// if (g_signal == SIGINT)
	// {
	// 	if (access(filename, F_OK) != -1)
	// 		unlink(filename);
	// 	return (close(fd), EINTR);
	// }
	free((*cmd)->infile);
	(*cmd)->infile = ft_strdup(filename);
	if ((*cmd)->infile == NULL)
		return (close(fd), perror("Error"), ENOMEM);
	return (close(fd), 0);
}
