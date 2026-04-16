/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esezalor <esezalor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 17:56:59 by jille             #+#    #+#             */
/*   Updated: 2026/04/16 21:24:13 by esezalor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headerfiles/minishell.h"

int	process_heredoc(t_token *tokens, t_cmd *cmd)
{
	free(cmd->heredoc_delim);
	cmd->heredoc_delim = ft_strdup(tokens->content);
	if (!cmd->heredoc_delim)
		return (errno);
	return (heredoc_to_file(&cmd));
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

void	heredoc_loop(t_cmd **cmd, int h_fd)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			write(2, "jeis: warning: h-doc delimited by end-of-file (wanted `",
				56);
			write(2, (*cmd)->heredoc_delim, strlen((*cmd)->heredoc_delim));
			write(2, "')\n", 3);
			break ;
		}
		if (g_signal == SIGINT)
			return (free(line));
		if (ft_strncmp(line, (*cmd)->heredoc_delim,
				(ft_strlen((*cmd)->heredoc_delim) + 1)) == 0)
			return (free(line));
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

	if (h_num > 0)
		if (access((*cmd)->infile, F_OK) != -1)
			unlink((*cmd)->infile);
	if (!(*cmd)->heredoc_delim)
		return (print_syntax_error(NULL));
	filename = create_heredoc_file_name(h_num++);
	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		return (perror("heredoc hiddenfile open"), ENOENT);
	heredoc_loop(cmd, fd);
	if (g_signal == SIGINT)
	{
		if (access(filename, F_OK) != -1)
			unlink(filename);
		return (close(fd), EINTR);
	}
	free((*cmd)->infile);
	(*cmd)->infile = ft_strdup(filename);
	if ((*cmd)->infile == NULL)
		return (close(fd), perror("Error"), ENOMEM);
	return (close(fd), 0);
}
