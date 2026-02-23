/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esezalor <esezalor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 13:56:33 by esezalor          #+#    #+#             */
/*   Updated: 2026/02/03 15:36:46 by esezalor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	wordcount(char const *s, char c)
{
	int	i;
	int	count;
	int	in_word;

	i = 0;
	count = 0;
	in_word = 0;
	while (s[i])
	{
		if (s[i] != c)
			in_word = 1;
		if (s[i] == c && in_word == 1)
		{
			in_word = 0;
			count++;
		}
		if (s[i] != c && s[i + 1] == '\0')
			count++;
		i++;
	}
	return (count);
}

static char	*generate_string(char const *s, char c)
{
	size_t	i;
	char	*strblock;

	i = 0;
	while (s[i] && s[i] != c && s[i] != '\n')
		i++;
	strblock = (char *)malloc((sizeof(char) * i) + 1);
	if (!strblock)
		return (NULL);
	ft_memcpy(strblock, s, i);
	strblock[i] = '\0';
	return (strblock);
}

static void	ft_free(char **str_array, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (str_array[i])
			free(str_array[i]);
		i++;
	}
	free(str_array);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	j;
	char	**str_array;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	str_array = (char **)malloc(sizeof(char *) * (wordcount(s, c) + 1));
	if (!str_array)
		return (free(str_array), NULL);
	while (s[i] && j < ((size_t)wordcount(s, c)))
	{
		while (s[i] && s[i] == c)
			i++;
		str_array[j] = generate_string(s + i, c);
		if (!str_array[j])
			return (ft_free(str_array, j), NULL);
		while (s[i] && s[i] != c)
			i++;
		j++;
	}
	str_array[j] = NULL;
	return (str_array);
}

/*#include <stdio.h>
#include <stdlib.h> // for free()

static void	print_result(char **result)
{
	int	i;

	i = 0;
	if (!result)
	{
		printf("NULL returned\n");
		return ;
	}
	while (result[i])
	{
		printf("[%d] \"%s\"\n", i, result[i]);
		i++;
	}
}

static void	free_result(char **result)
{
	int	i;

	i = 0;
	if (!result)
		return ;
	while (result[i])
		free(result[i++]);
	free(result);
}

int	main(void)
{
	char	**res;

	// Test 1: Normal sentence
	printf("Test 1: \"Hello World This Is 42\" split by space\n");
	res = ft_split("Hello World This Is 42", ' ');
	print_result(res);
	free_result(res);
	printf("\n");

	// Test 2: Multiple consecutive delimiters
	printf("Test 2: \"Hello,,World,,42\" split by ','\n");
	res = ft_split("Hello,,World,,42", ',');
	print_result(res);
	free_result(res);
	printf("\n");

	// Test 3: Starting and ending delimiters
	printf("Test 3: \",,Split,This,\" split by ','\n");
	res = ft_split(",,Split,This,", ',');
	print_result(res);
	free_result(res);
	printf("\n");

	// Test 4: Empty string
	printf("Test 4: \"\" split by ','\n");
	res = ft_split("", ',');
	print_result(res);
	free_result(res);
	printf("\n");

	// Test 5: NULL string (should return NULL safely)
	printf("Test 5: NULL string\n");
	res = ft_split(NULL, ',');
	print_result(res);
	free_result(res);
	printf("\n");
	return (0);
}*/
