/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_libftutils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jille <jille@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 11:38:21 by esezalor          #+#    #+#             */
/*   Updated: 2026/04/21 18:05:45 by jille            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

long long	ft_atol(const char *nptr, int *overflow_flag)
{
	int			i;
	int			sign;
	long long	new_nbr;

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
	while (nptr[i] == '0')
		i++;
	if (ft_atol_overflow(&nptr[i], sign) == 1)
		return (*overflow_flag = 1, 2147483648);
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		new_nbr = (new_nbr * 10) + (nptr[i] - 48);
		i++;
	}
	return (new_nbr * sign);
}

int	ft_atol_overflow(const char *nptr, int sign)
{
	const char	*limit;
	int			len;

	if (sign == -1)
		limit = "9223372036854775808";
	else
		limit = "9223372036854775807";
	len = 0;
	while (nptr[len] >= '0' && nptr[len] <= '9')
		len++;
	if (len > 19)
		return (1);
	if (len == 19 && ft_strncmp(nptr, limit, 19) > 0)
		return (1);
	while (nptr[len] == ' ' || (nptr[len] >= 9 && nptr[len] <= 13))
		len++;
	if (nptr[len] != '\0')
		return (0);
	return (0);
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
