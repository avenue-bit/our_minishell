/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esezalor <esezalor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 10:07:59 by esezalor          #+#    #+#             */
/*   Updated: 2026/01/05 18:04:29 by esezalor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t				i;
	const unsigned char	*ps;
	unsigned char		uc;

	i = 0;
	ps = (unsigned char *)s;
	uc = (unsigned char)c;
	while (ps[i])
	{
		if (ps[i] == uc)
			return ((char *)&ps[i]);
		i++;
	}
	if (ps[i] == uc)
		return ((char *)&ps[i]);
	return (NULL);
}
