/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esezalor <esezalor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 11:48:26 by esezalor          #+#    #+#             */
/*   Updated: 2025/10/15 17:55:58 by esezalor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	in_set(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	s1_len;
	size_t	final_len;
	char	*trimmed;

	i = 0;
	if (!s1 || !set)
		return (NULL);
	s1_len = ft_strlen(s1);
	while (s1[i] && in_set(s1[i], set))
		i++;
	while (s1_len > i && s1[s1_len - 1] && in_set(s1[s1_len - 1], set))
		s1_len--;
	final_len = s1_len - i;
	trimmed = (char *)malloc(final_len + 1);
	if (!trimmed)
		return (NULL);
	ft_memcpy(trimmed, s1 + i, final_len);
	trimmed[final_len] = '\0';
	return (trimmed);
}
