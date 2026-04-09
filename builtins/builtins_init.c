/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esezalor <esezalor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 16:57:46 by esezalor          #+#    #+#             */
/*   Updated: 2026/04/09 10:33:31 by esezalor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	is_builtin(t_exec *storage, char *command)
{
	int	cmd_len;
	int	i;

	if (!command || !*command)
		return (0);
	storage->builtins[0] = "echo";
	storage->builtins[1] = "cd";
	storage->builtins[2] = "pwd";
	storage->builtins[3] = "export";
	storage->builtins[4] = "unset";
	storage->builtins[5] = "env";
	storage->builtins[6] = "exit";
	storage->builtins[7] = NULL;
	cmd_len = ft_strlen(command);
	i = 0;
	while (storage->builtins[i])
	{
		if (ft_strncmp(command, storage->builtins[i], cmd_len + 1) == 0)
			return (1);
		i++;
	}
	return (0);
}

void	built_init(t_exec *storage)
{
	storage->builtin_func[0] = ft_echo;
	storage->builtin_func[1] = ft_cd;
	storage->builtin_func[2] = ft_pwd;
	storage->builtin_func[3] = ft_export;
	storage->builtin_func[4] = ft_unset;
	storage->builtin_func[5] = ft_env;
	storage->builtin_func[6] = ft_exit;
	storage->builtin_func[7] = NULL;
}

int	exec_builtin(t_exec *storage, t_cmd *cmd_node)
{
	int	i;
	int	cmd_len;

	cmd_len = ft_strlen(cmd_node->cmd_flags[0]);
	i = 0;
	while (storage->builtins[i])
	{
		if (ft_strncmp(cmd_node->cmd_flags[0], storage->builtins[i], cmd_len
				+ 1) == 0)
			return ((*storage->builtin_func[i])(storage, cmd_node));
		i++;
	}
	return (0);
}

void	builtin_dup(t_exec *storage, t_cmd *cmd_node)
{
	storage->built_in = dup(0);
	if (storage->built_in == -1)
		return (freeing_ramp(storage), exit(1));
	storage->built_out = dup(1);
	if (storage->built_out == -1)
		return (freeing_ramp(storage), exit(1));
	if (infile_outfile_check(storage, cmd_node))
		storage->exit_code = exec_builtin(storage, cmd_node);
	else
		storage->exit_code = 1;
	if (dup2(storage->built_in, 0) == -1)
		return (freeing_ramp(storage), exit(1));
	if (dup2(storage->built_out, 1) == -1)
		return (freeing_ramp(storage), exit(1));
	close(storage->built_in);
	close(storage->built_out);
}
