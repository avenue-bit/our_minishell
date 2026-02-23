/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esezalor <esezalor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 19:38:31 by esezalor          #+#    #+#             */
/*   Updated: 2025/10/15 17:42:58 by esezalor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	size_nb(int n)
{
	long int	len;
	long int	long_n;

	len = 0;
	long_n = n;
	if (long_n == 0)
		len++;
	if (long_n < 0)
	{
		long_n = -long_n;
		len++;
	}
	while (long_n > 0)
	{
		long_n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	long int	long_n;
	long int	str_size;
	char		*str;

	long_n = (long int)n;
	str_size = size_nb(n);
	str = malloc(sizeof(char) * (str_size + 1));
	if (!str)
		return (NULL);
	if (long_n == 0)
		str[0] = '0';
	if (n < 0)
	{
		long_n *= -1;
		str[0] = '-';
	}
	while (long_n > 0)
	{
		str[--str_size] = ((long_n % 10) + 48);
		long_n /= 10;
	}
	str[size_nb(n)] = '\0';
	return (str);
}
