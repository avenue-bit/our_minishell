/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esezalor <esezalor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 11:16:41 by esezalor          #+#    #+#             */
/*   Updated: 2026/01/25 16:03:38 by esezalor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_atoi(const char *nptr)
{
	int			i;
	int			sign;
	long long	new_nbr;

	i = 0;
	sign = 1;
	new_nbr = 0;
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

// int	main(void)
// {
// 	printf("%d\n", ft_atoi("   -1234abc"));
// 	printf("%d\n", ft_atoi("42"));
// 	printf("%d\n", ft_atoi("   +0"));
// 	printf("%d\n", ft_atoi("00000000123"));
// 	printf("%d\n", ft_atoi("2147483647"));
// 	printf("%d\n", ft_atoi("-2147483648"));
// 	return (0);
// }