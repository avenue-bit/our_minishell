/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_ft2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esezalor <esezalor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 16:57:46 by esezalor          #+#    #+#             */
/*   Updated: 2026/03/18 11:58:02 by esezalor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_exec *storage, t_cmd *cmd_node)
{
	int	i;

	i = 0;
	while (storage->execve_env[i])
	{
		ft_printf("%s\n", storage->execve_env[i]);
		i++;
	}
	return (0);
}

int	ft_exit(t_exec *storage, t_cmd *cmd_node)
{
	return (0);
}
