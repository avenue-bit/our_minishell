/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jille <jille@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 17:56:59 by jille             #+#    #+#             */
/*   Updated: 2026/04/26 15:30:12 by jille            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	process_heredoc(t_token *tokens, t_cmd *cmd, t_exec *storage)
{
	free(cmd->heredoc_delim);
	cmd->heredoc_expand = !check_quotes(tokens->content);
	cmd->heredoc_delim = strip_quotes_str(tokens->content);
	if (!cmd->heredoc_delim)
		return (ENOMEM);
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

int	heredoc_warning(t_cmd *cmd)
{
	write(2, "jeis: warning: h-doc delimited by end-of-file (wanted `", 55);
	write(2, (cmd)->heredoc_delim, ft_strlen((cmd)->heredoc_delim));
	write(2, "')\n", 3);
	return (0);
}

int	heredoc_loop(t_cmd *cmd, int h_fd, t_exec *storage)
{
	char	*line;
	int		status;

	while (1)
	{
		line = mini_nextline(0);
		if (!line)
			return (heredoc_warning(cmd));
		if (g_signal == SIGINT)
			return (free(line), EINTR);
		if (ft_strncmp(line, (cmd)->heredoc_delim,
				(ft_strlen((cmd)->heredoc_delim) + 1)) == 0)
			return (free(line), 0);
		if ((cmd)->heredoc_expand)
			status = expand_heredoc_line(line, storage, h_fd);
		else
		{
			write(h_fd, line, ft_strlen(line));
			free(line);
			status = 0;
		}
		if (status != 0)
			return (status);
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
	status = heredoc_loop(*cmd, fd, storage);
	if (status != 0)
		return (close_unlink(fd, filename), status);
	free((*cmd)->infile);
	(*cmd)->infile = ft_strdup(filename);
	if ((*cmd)->infile == NULL)
		return (close_unlink(fd, filename), perror("Error"), ENOMEM);
	return (close(fd), 0);
}
