/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esezalor <esezalor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 18:12:57 by esezalor          #+#    #+#             */
/*   Updated: 2026/02/25 16:55:21 by esezalor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	extract_path(t_shell *shell_storage)
{
	int		n_paths;
	t_env	*environment;

	environment = shell_storage->environment;
	while (environment)
	{
		if (ft_strncmp(environment->key, "PATH", ft_strlen("PATH")) == 0)
			break ;
		environment = environment->next;
	}
	shell_storage->absolute_paths = ft_split(environment->content, ':');
	if (!shell_storage->absolute_paths)
		return (-1);
	n_paths = 0;
	while (shell_storage->absolute_paths[n_paths])
		n_paths++;
	return (n_paths);
}

char	*pathfinder(t_shell *shell_storage, char *command)
{
	int		i;
	int		path_len;
	char	*is_valid;
	char	**path;

	path = shell_storage->absolute_paths;
	i = 0;
	while (path[i])
	{
		path_len = ft_strlen(path[i]);
		is_valid = calloc(path_len + ft_strlen(command) + 2, sizeof(char));
		if (!is_valid)
			return (NULL);
		ft_memcpy(is_valid, path[i], path_len);
		is_valid[path_len] = '/';
		ft_memcpy(is_valid + path_len + 1, command, ft_strlen(command));
		if (access(is_valid, X_OK) == 0)
			break ;
		free(is_valid);
		is_valid = NULL;
		i++;
	}
	return (is_valid);
}

int	main(int argc, char **argv, char **envp)
{
	char *pathname;
	t_shell storage; // RENAME LATER

	ft_bzero(&storage, sizeof(t_shell));
	if (argc < 1)
		return (0);
	pathname = "/usr/bin/ls";
	storage.environment = envnodes_init(envp);
	storage.execve_env = envarray_init(storage.environment);
	if (!storage.execve_env)
		return (env_clearnode(&storage.environment), 0);
	if (extract_path(&storage) == -1)
	{
		ft_arrayfree(storage.execve_env, ft_envsize(storage.environment));
		env_clearnode(&storage.environment);
		return (-1);
	}
	storage.command_path = pathfinder(&storage, argv[1]);
	if (!storage.command_path)
	{
		ft_arrayfree(storage.absolute_paths, extract_path(&storage));
		ft_arrayfree(storage.execve_env, ft_envsize(storage.environment));
		env_clearnode(&storage.environment);
		return (-1);
	}
	execve(storage.command_path, &argv[1], storage.execve_env);
	return (0);
}