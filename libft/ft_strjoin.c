/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esezalor <esezalor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 10:47:42 by esezalor          #+#    #+#             */
/*   Updated: 2026/02/06 14:49:28 by esezalor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	size_t	total_len;
	char	*output;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	total_len = s1_len + s2_len;
	output = NULL;
	output = ft_calloc(total_len + 1, sizeof(char));
	if (!output)
		return (NULL);
	ft_memcpy(output, s1, s1_len);
	ft_memcpy(output + s1_len, s2, s2_len);
	output[s1_len + s2_len] = '\0';
	return (output);
}

/*#include <stdio.h>
#include <stdlib.h> // for free()

int	main(void)
{
	char	*res;

	// Test 1: Normal join
	res = ft_strjoin("Hello", "World");
	printf("Test 1: Join \"Hello\" + \"World\"\n");
	printf("  Result: \"%s\"\n\n", res);
	free(res);

	// Test 2: Add space between
	res = ft_strjoin("Hello ", "World");
	printf("Test 2: Join \"Hello \" + \"World\"\n");
	printf("  Result: \"%s\"\n\n", res);
	free(res);

	// Test 3: One empty string
	res = ft_strjoin("", "World");
	printf("Test 3: Join \"\" + \"World\"\n");
	printf("  Result: \"%s\"\n\n", res);
	free(res);

	res = ft_strjoin("Hello", "");
	printf("Test 3b: Join \"Hello\" + \"\"\n");
	printf("  Result: \"%s\"\n\n", res);
	free(res);

	// Test 4: Both empty strings
	res = ft_strjoin("", "");
	printf("Test 4: Join \"\" + \"\"\n");
	printf("  Result: \"%s\"\n\n", res);
	free(res);

	// Test 5: NULL protection (should safely return NULL)
	res = ft_strjoin(NULL, "World");
	printf("Test 5: s1 = NULL\n");
	printf("  Result: %s\n\n", res ? res : "NULL");

	res = ft_strjoin("Hello", NULL);
	printf("Test 6: s2 = NULL\n");
	printf("  Result: %s\n\n", res ? res : "NULL");

	return (0);
}*/