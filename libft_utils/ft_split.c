/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esezalor <esezalor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 19:50:26 by jille             #+#    #+#             */
/*   Updated: 2026/04/09 11:25:52 by esezalor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headerfiles/minishell.h"

void	split_f(char **strarr)
{
	int	i;

	i = 0;
	if (!strarr)
		return ;
	while (strarr[i] != NULL)
	{
		free(strarr[i]);
		strarr[i] = NULL;
		i++;
	}
	free(strarr);
	return ;
}

static char	**free_all(char **strarr, int i)
{
	while (i-- > 0)
	{
		free(strarr[i]);
		strarr[i] = NULL;
	}
	free(strarr);
	strarr = NULL;
	return (NULL);
}

static int	word_count(char const *s, char c)
{
	int	i;
	int	wc;

	i = 0;
	wc = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] && ++wc)
		{
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (wc);
}

static char	**create_array(char **strarr, char *begw, char c, int wc)
{
	int		k;
	int		i;
	char	*endw;

	i = 0;
	while (wc--)
	{
		k = 0;
		if (i > 0 && *begw != c)
			begw = ft_strchr(begw, c);
		while (*begw && *begw == c)
			begw++;
		endw = ft_strchr(begw, c);
		if (!endw)
			endw = ft_strchr(begw, '\0');
		strarr[i] = malloc((ft_strlen(begw) - ft_strlen(endw) + 1)
				* sizeof(char));
		if (!strarr[i])
			return (free_all(strarr, i));
		while (begw < endw)
			strarr[i][k++] = *begw++;
		strarr[i++][k] = '\0';
	}
	strarr[i] = NULL;
	return (strarr);
}

char	**ft_split(const char *s, char c)
{
	int		wc;
	char	**strarr;
	char	*begw;

	if (!*s)
	{
		strarr = malloc(sizeof(char *));
		if (!strarr)
			return (NULL);
		strarr[0] = NULL;
		return (strarr);
	}
	wc = word_count(s, c);
	strarr = malloc(sizeof(char *) * (wc + 1));
	if (!strarr)
		return (NULL);
	begw = (char *)s;
	strarr = create_array(strarr, begw, c, wc);
	return (strarr);
}
