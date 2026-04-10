/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_libftutils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jille <jille@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 11:29:21 by esezalor          #+#    #+#             */
/*   Updated: 2026/04/10 15:16:54 by jille            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headerfiles/minishell.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (*s == (char)c)
		return ((char *)s);
	return (NULL);
}

char	*ft_strdup(const char *s)
{
	int		i;
	char	*new_string;

	i = 0;
	while (s[i])
		i++;
	new_string = malloc(sizeof(char) * (i + 1));
	if (new_string == NULL)
		return (NULL);
	i = 0;
	while (*s)
	{
		new_string[i++] = *s;
		s++;
	}
	new_string[i] = '\0';
	return (new_string);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*joinstr;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1)
		return (ft_strjoin("", s2));
	if (!s2)
		return (ft_strjoin(s1, ""));
	joinstr = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!joinstr)
		return (NULL);
	while (s1[i])
		joinstr[j++] = s1[i++];
	i = 0;
	while (s2[i])
		joinstr[j++] = s2[i++];
	joinstr[j] = '\0';
	return (joinstr);
}

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (n == 0)
		return (0);
	while (--n > 0 && (*s1 && *s2))
	{
		if (*s1 != *s2)
			return ((unsigned char)*s1 - (unsigned char)*s2);
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}
