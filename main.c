/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esezalor <esezalor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 18:12:57 by esezalor          #+#    #+#             */
/*   Updated: 2026/02/25 18:05:54 by esezalor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_shell storage; // RENAME LATER

	ft_bzero(&storage, sizeof(t_shell));
	if (argc < 1)
		return (0);
	storage.environment = envnodes_init(envp);
	storage.execve_env = envarray_init(storage.environment);
	if (!storage.execve_env)
		return (env_clearnode(&storage.environment), 0);
	if (path_ramp(&storage, argv) == -1)
		return (env_clearnode(&storage.environment), 0); // Error
	execve(storage.command_path, &argv[1], storage.execve_env);
	return (0);
}