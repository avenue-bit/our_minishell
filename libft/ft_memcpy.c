/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esezalor <esezalor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 16:38:24 by esezalor          #+#    #+#             */
/*   Updated: 2025/10/15 17:43:42 by esezalor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	const unsigned char	*psrc;
	unsigned char		*pdest;

	psrc = (unsigned char *)src;
	pdest = (unsigned char *)dest;
	while (n--)
		*pdest++ = *psrc++;
	return (dest);
}
