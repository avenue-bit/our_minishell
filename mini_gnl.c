/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_gnl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jille <jille@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 14:32:04 by esezalor          #+#    #+#             */
/*   Updated: 2026/04/19 12:18:53 by jille            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 42
#endif

#include "minishell.h"

char	*mini_nextline(int fd)
{
	char		*buffer;
	static char	*stash;
	char		*fdf_line;

	if (fd == -1)
		return (free(stash), stash = NULL, NULL);
	if (fd < -1 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
	{
		if (stash)
			return (free(stash), stash = NULL, NULL);
		return (NULL);
	}
	stash = update_stash(fd, stash, buffer);
	if (!stash)
		return (free(buffer), NULL);
	fdf_line = extract(stash);
	if (!fdf_line)
		return (free(buffer), free(stash), stash = NULL, NULL);
	stash = the_rest(stash);
	if (!stash)
		return (free(buffer), fdf_line);
	return (free(buffer), fdf_line);
}

char	*update_stash(int fd, char *stash, char *buffer)
{
	int		bytes_read;
	char	*temp;

	bytes_read = 1;
	while ((!stash || !ft_strchr(stash, '\n')) && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free(stash), stash = NULL, NULL);
		if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		if (!stash)
		{
			stash = ft_strdup("");
			if (!stash)
				return (NULL);
		}
		temp = ft_strjoin(stash, buffer);
		if (!temp)
			return (free(stash), stash = NULL, NULL);
		free(stash);
		stash = temp;
	}
	return (stash);
}

char	*extract(char *str)
{
	int		i;
	int		k;
	char	*newline;

	i = 0;
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	newline = ft_calloc(i + 2, sizeof(char));
	if (!newline)
		return (NULL);
	k = 0;
	while (k <= i)
	{
		newline[k] = str[k];
		k++;
	}
	return (newline);
}

char	*the_rest(char *stash)
{
	char	*temp;
	int		len;
	int		i;
	int		k;

	if (!stash || ft_strchr(stash, '\n') == 0 || ft_strlen(ft_strchr(stash,
				'\n')) == 1)
		return (free(stash), stash = NULL, NULL);
	len = ft_strlen(ft_strchr(stash, '\n')) - 1;
	temp = ft_calloc(len + 1, sizeof(char));
	if (!temp)
		return (free(stash), stash = NULL, NULL);
	i = 0;
	while (stash[i] != '\n')
		i++;
	k = 0;
	while (k <= len)
	{
		temp[k] = stash[i + 1];
		k++;
		i++;
	}
	free(stash);
	stash = temp;
	return (stash);
}
