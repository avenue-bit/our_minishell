/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adhoc_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jille <jille@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 11:52:31 by esezalor          #+#    #+#             */
/*   Updated: 2026/04/19 12:18:41 by jille            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_arrayfree(char **str_array)
{
	int	i;

	i = 0;
	if (!str_array)
		return ;
	while (str_array[i])
	{
		if (str_array[i])
		{
			free(str_array[i]);
			str_array[i] = NULL;
		}
		i++;
	}
	free(str_array);
}

int	ft_envsize(t_env *lst)
{
	int	size;

	if (!lst)
		return (0);
	size = 1;
	while (lst->next)
	{
		lst = lst->next;
		size++;
	}
	return (size);
}

size_t	n_commands(t_cmd *cmd)
{
	int	size;

	if (!cmd)
		return (0);
	size = 1;
	while (cmd->next)
	{
		cmd = cmd->next;
		size++;
	}
	return (size);
}

int	find_char(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void	error_message_helper(char *command, char *suffix, int fd)
{
	char	*err_message;
	int		len;

	err_message = ft_strjoin(command, suffix);
	if (!err_message)
		return ;
	len = ft_strlen(err_message);
	write(fd, err_message, len);
	free(err_message);
	err_message = NULL;
}
