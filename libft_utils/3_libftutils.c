/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_libftutils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esezalor <esezalor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 11:38:21 by esezalor          #+#    #+#             */
/*   Updated: 2026/04/03 12:18:58 by esezalor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_utils.h"

int	ft_isalpha(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

void	ft_putstr_fd(char *s, int fd)
{
	write(fd, s, ft_strlen(s));
}

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

long	ft_atol(const char *nptr)
{
	int			i;
	int			sign;
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
