/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_ft1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esezalor <esezalor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 16:57:46 by esezalor          #+#    #+#             */
/*   Updated: 2026/03/18 19:46:14 by esezalor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Dont forget to replace with ft_printf

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

int	ft_cd(t_exec *storage, t_cmd *cmd_node)
{
	char	*pwd_path;
	char	*target_path;
	char	*old_pwd;

	if (cmd_node->cmd_flags[1] && cmd_node->cmd_flags[2])
		return (ft_printf("Too many arguments for cd\n"), 1); // Error Handling Needed
	pwd_path = cd_path(storage, "PWD", 4);
	if (!pwd_path)
		old_pwd = ft_strdup("");
	else
		old_pwd = ft_strdup(pwd_path);
	if (!old_pwd)
		return (1);
	target_path = get_target_path(storage, cmd_node->cmd_flags[1]);
	if (!target_path)
		return (free(old_pwd), ft_printf("home not set\n"), 1); // Error Handling Needed
	if (chdir(target_path) == -1)
		return (free(old_pwd), ft_printf("could not change directory\n"), 1); // Error Handling Needed
	if (replace_pwd(storage, old_pwd) == -1)
		return (free(old_pwd), 1);
	return (0);
}

int	ft_pwd(t_exec *storage, t_cmd *cmd_node)
{
	t_env	*current;

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
	return (1);
}

int	ft_export(t_exec *storage, t_cmd *cmd_node)
{
	return (0);
}

int	ft_unset(t_exec *storage, t_cmd *cmd_node)
{
	return (0);
}
