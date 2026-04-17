/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esezalor <esezalor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 17:31:17 by jille             #+#    #+#             */
/*   Updated: 2026/04/17 12:37:57 by esezalor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headerfiles/minishell.h"

int	fill_cmd_data_redir(t_token **tokens, t_cmd *cmd)
{
	t_type	type;
	int		fd;

	type = (*tokens)->type;
	*tokens = (*tokens)->next;
	if (!*tokens)
		return (ENOMEM);
	errno = 0;
	if (type == tk_HERE_DOC)
		return (process_heredoc(*tokens, cmd));
	if (type == tk_REDIR_IN)
		fd = open((*tokens)->content, O_RDONLY);
	else if (type == tk_APPEND)
		fd = open((*tokens)->content, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open((*tokens)->content, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (perror((*tokens)->content), ENOENT);
	close(fd);
	errno = 0;
	return (set_redir_path(cmd, tokens, type));
}

int	fill_node_data(t_token **tokens, t_cmd *cmd, int *i)
{
	int	reint;

	if ((*tokens)->type == tk_WORD)
	{
		cmd->cmd_flags[*i] = ft_strdup((*tokens)->content);
		if (!cmd->cmd_flags[(*i)++])
			return (ENOMEM);
	}
	else if ((*tokens)->type >= tk_REDIR_IN && (*tokens)->type <= tk_APPEND)
	{
		reint = fill_cmd_data_redir(tokens, cmd);
		if (reint != 0)
			return (reint);
	}
	return (0);
}

int	fill_cmd_data(t_token **tokens, t_cmd *cmd)
{
	int	i;
	int	reint;

	i = 0;
	while (*tokens && (*tokens)->type != tk_PIPE)
	{
		reint = fill_node_data(tokens, cmd, &i);
		if (reint == ENOMEM)
			return (perror("Error"), ENOMEM);
		if (reint == ENOENT)
		{
			while (*tokens && (*tokens)->type != tk_PIPE)
				*tokens = (*tokens)->next;
			return (ENOENT);
		}
		if (reint == EINTR)
			return (EINTR);
		if (*tokens)
			*tokens = (*tokens)->next;
	}
	return (0);
}

t_cmd	*init_new_cmd(t_cmd **cmd_list, t_token *tokens)
{
	t_cmd	*current_cmd;

	current_cmd = add_cmd_node(cmd_list);
	if (!current_cmd)
		return (NULL);
	current_cmd->cmd_flags = ft_calloc((count_tokens_words(tokens) + 1),
			sizeof(char *));
	if (!current_cmd->cmd_flags)
		return (remove_last_cmd_node(cmd_list, current_cmd), NULL);
	return (current_cmd);
}

void	create_cmd_list(t_cmd **cmd_list, t_token *tokens, t_exec *storage)
{
	t_token	*tmp;
	int		reint;
	t_cmd	*current_cmd;

	if (!tokens)
		return ;
	tmp = tokens;
	while (tmp)
	{
		current_cmd = init_new_cmd(cmd_list, tmp);
		if (!current_cmd)
			return (freeing_ramp(storage), perror("Error"), exit(errno));
		reint = fill_cmd_data(&tmp, current_cmd);
		if (reint == ENOMEM)
			return (freeing_ramp(storage), perror("Error"), exit(errno));
		if (reint == ENOENT)
			remove_last_cmd_node(cmd_list, current_cmd);
		if (reint == EINTR)
			return ;
		if (tmp && tmp->type == tk_PIPE)
			tmp = tmp->next;
	}
}
