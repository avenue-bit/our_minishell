/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_basic.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esezalor <esezalor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 16:57:46 by esezalor          #+#    #+#             */
/*   Updated: 2026/04/14 16:13:11 by esezalor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headerfiles/minishell.h"

int	ft_echo(t_exec *storage, t_cmd *cmd_node)
{
	int	i;
	int	j;

	(void)storage;
	if (!cmd_node->cmd_flags[1])
		return (ft_printf("\n"), 0);
	i = newline_flag(cmd_node->cmd_flags);
	j = i;
	if (cmd_node->cmd_flags[j])
	{
		ft_printf("%s", cmd_node->cmd_flags[j]);
		j++;
	}
	while (cmd_node->cmd_flags[j])
	{
		ft_printf(" %s", cmd_node->cmd_flags[j]);
		j++;
	}
	if (i == 1)
		ft_printf("\n");
	return (0);
}

int	ft_pwd(t_exec *storage, t_cmd *cmd_node)
{
	t_env	*current;
	char	*buffer;

	(void)cmd_node;
	current = storage->environment;
	while (current)
	{
		if (ft_strncmp(current->key, "PWD", ft_strlen("PWD")) == 0)
		{
			ft_printf("%s\n", current->content);
			return (0);
		}
		current = current->next;
	}
	buffer = ft_calloc(PATH_MAX, sizeof(char));
	if (!buffer)
		return (1);
	if (!getcwd(buffer, PATH_MAX))
		return (free(buffer), 1);
	ft_printf("%s\n", buffer);
	free(buffer);
	return (0);
}

int	ft_env(t_exec *storage, t_cmd *cmd_node)
{
	int	i;

	(void)cmd_node;
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
	long	exit_code;

	if (!cmd_node->cmd_flags[1])
		return (storage->exit_flag = 1, ft_printf("exit\n"),
			storage->exit_code);
	if (isvalid_exitcode(cmd_node->cmd_flags[1]))
		return (storage->exit_flag = 1, ft_exit_message(cmd_node->cmd_flags[1]),
			2);
	if (cmd_node->cmd_flags[2])
		return (ft_putstr_fd("exit\n", 2),
			ft_putstr_fd("bash: exit: too many arguments\n", 2), 1);
	exit_code = ft_atol(cmd_node->cmd_flags[1]);
	if (exit_code > INT_MAX)
		return (storage->exit_flag = 1, ft_exit_message(cmd_node->cmd_flags[1]),
			2);
	exit_code = (exit_code % 256 + 256) % 256;
	return (storage->exit_flag = 1, ft_putstr_fd("exit\n", 2), exit_code);
}
