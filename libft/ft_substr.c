/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esezalor <esezalor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 10:12:50 by esezalor          #+#    #+#             */
/*   Updated: 2025/10/13 12:37:11 by esezalor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substring;
	size_t	str_size;
	size_t	i;
	size_t	st;

	if (!s)
		return (NULL);
	str_size = ft_strlen(s);
	st = (size_t)start;
	if (start >= str_size)
		i = 0;
	else if (len < str_size - st)
		i = len;
	else
		i = str_size - st;
	substring = (char *)malloc(i + 1);
	if (!substring)
		return (NULL);
	ft_memcpy(substring, s + start, i);
	substring[i] = '\0';
	return (substring);
}

/*#include <stdio.h>
#include <stdlib.h> // for free()

char	*ft_substr(char const *s, unsigned int start, size_t len);

int	main(void)
{
	char	*res;

	// Test 1: Normal substring
	res = ft_substr("Hello World", 6, 5);
	printf("Test 1: start=6, len=5 -> \"%s\"\n", res);
	free(res);

	// Test 2: Substring from start
	res = ft_substr("Hello World", 0, 5);
	printf("Test 2: start=0, len=5 -> \"%s\"\n", res);
	free(res);

	// Test 3: len larger than string
	res = ft_substr("Hello", 1, 50);
	printf("Test 3: start=1, len=50 -> \"%s\"\n", res);
	free(res);

	// Test 4: start beyond string length
	res = ft_substr("Hello", 10, 5);
	printf("Test 4: start=10, len=5 -> \"%s\"\n", res);
	free(res);

	// Test 5: len = 0
	res = ft_substr("Hello", 2, 0);
	printf("Test 5: start=2, len=0 -> \"%s\"\n", res);
	free(res);

	// Test 6: Empty string
	res = ft_substr("", 0, 5);
	printf("Test 6: empty string -> \"%s\"\n", res);
	free(res);

	// Test 7: NULL string (should return NULL safely)
	res = ft_substr(NULL, 0, 5);
	printf("Test 7: s = NULL -> %s\n", res ? res : "NULL");

	return (0);
}*/
