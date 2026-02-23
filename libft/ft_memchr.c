/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esezalor <esezalor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 18:07:23 by esezalor          #+#    #+#             */
/*   Updated: 2025/10/15 17:43:19 by esezalor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*pstr;

	pstr = (unsigned char *)s;
	while (n--)
	{
		if (*pstr == (unsigned char)c)
			return (pstr);
		pstr++;
	}
	return (NULL);
}
