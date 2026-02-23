/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esezalor <esezalor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 14:07:06 by esezalor          #+#    #+#             */
/*   Updated: 2025/10/15 17:55:39 by esezalor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int				i;
	const char		*p = s;
	unsigned char	uc;

	i = 0;
	uc = (unsigned char)c;
	while (p[i])
		i++;
	while (i >= 0)
	{
		if ((unsigned char)p[i] == uc)
			return ((char *)(p + i));
		if (i == 0)
			return (NULL);
		i--;
	}
	return (NULL);
}
