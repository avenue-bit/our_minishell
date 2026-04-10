/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_libftutils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esezalor <esezalor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 11:38:21 by esezalor          #+#    #+#             */
/*   Updated: 2026/04/10 19:14:36 by esezalor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headerfiles/minishell.h"

long	ft_atol(const char *nptr)
{
	int		i;
	int		sign;
	long	new_nbr;

	i = 0;
	sign = 1;
	new_nbr = 0;
	while (nptr[i] == ' ' || nptr[i] == '\t')
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		new_nbr = (new_nbr * 10) + (nptr[i] - 48);
		if (new_nbr > INT_MAX || new_nbr < INT_MIN)
			return (2147483648);
		i++;
	}
	return (new_nbr * sign);
}

char	*ft_itoa(int n)
{
	long	num;
	int		bytes;
	char	*numstr;

	num = n;
	bytes = (n < 0);
	if (n == 0)
		return (ft_strdup("0"));
	while (num && ++bytes)
		num /= 10;
	numstr = malloc(sizeof(char) * (bytes + 1));
	if (!numstr)
		return (NULL);
	numstr[bytes] = '\0';
	num = n;
	if (num < 0)
		num *= -1;
	while (num)
	{
		numstr[--bytes] = (num % 10) + 48;
		num /= 10;
	}
	if (n < 0)
		numstr[0] = '-';
	return (numstr);
}
