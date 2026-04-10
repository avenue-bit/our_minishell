/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_libftutils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esezalor <esezalor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 11:38:21 by esezalor          #+#    #+#             */
/*   Updated: 2026/04/10 19:14:56 by esezalor         ###   ########.fr       */
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
	if ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z') || (c >= 'a'
			&& c <= 'z'))
		return (1);
	return (0);
}
