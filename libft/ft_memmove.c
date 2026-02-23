/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esezalor <esezalor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 15:35:13 by esezalor          #+#    #+#             */
/*   Updated: 2026/01/25 16:03:31 by esezalor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*psrc;
	char	*pdest;

	if (!dest || !src || n == 0)
		return (dest);
	psrc = (char *)src;
	pdest = (char *)dest;
	if (pdest < psrc)
	{
		while (n--)
			*pdest++ = *psrc++;
	}
	else
	{
		while (n > 0)
		{
			pdest[n - 1] = psrc[n - 1];
			n--;
		}
	}
	return (dest);
}
