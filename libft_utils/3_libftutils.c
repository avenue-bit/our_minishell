/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_libftutils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jille <jille@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 11:38:21 by esezalor          #+#    #+#             */
/*   Updated: 2026/04/10 14:47:43 by jille            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headerfiles/minishell.h"

void	ft_putstr_fd(char *s, int fd)
{
	write(fd, s, ft_strlen(s));
}

int	ft_isalpha(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	ft_isalnum(int c)
{
	if ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z')
		|| (c >= 'a' && c <= 'z'))
		return (1);
	return (0);
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

