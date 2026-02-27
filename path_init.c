/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esezalor <esezalor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 17:48:46 by esezalor          #+#    #+#             */
/*   Updated: 2026/02/27 12:24:51 by esezalor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	path_ramp(t_shell *storage, char **argv)
{
	int	n_paths;

	// 1. Look for the Key "PATH" inside the environment list, 
	// extract, split and store each path in a string array stored in shell storage
	if (extract_path(storage) == -1)
	{
		ft_arrayfree(storage->execve_env, ft_envsize(storage->environment));
		return (-1);
	}
	// 2. Based on given command argv[1] append to each path and check if executable
	// return fully appended '/ + cmd' string of path 
	storage->command_path = pathfinder(storage, argv[1]);
	n_paths = 0;
	while (storage->all_paths && storage->all_paths[n_paths])
		n_paths++;
	ft_arrayfree(storage->all_paths, n_paths);
	if (!storage->command_path)
	{
		ft_arrayfree(storage->execve_env, ft_envsize(storage->environment));
		return (-1);
	}
	return (0);
}

int	extract_path(t_shell *shell_storage)
{
	t_env	*environment;

	environment = shell_storage->environment;
	while (environment)
	{
		if (ft_strncmp(environment->key, "PATH", 5) == 0)
			break ;
		environment = environment->next;
	}
	if (environment == NULL)
		return (-1); // Path Not found
	shell_storage->all_paths = ft_split(environment->content, ':');
	if (!shell_storage->all_paths)
		return (-1);
	return (0);
}

char	*pathfinder(t_shell *storage, char *command)
{
	int		i;
	char	*is_valid;
	char	**path;

	if (check_absolute(command) == 1)
		return (ft_strdup(command));
	path = storage->all_paths;
	i = 0;
	while (path && path[i])
	{
		is_valid = ft_calloc(ft_strlen(path[i]) + ft_strlen(command) + 2,
				sizeof(char));
		if (!is_valid)
			return (NULL);
		ft_memcpy(is_valid, path[i], ft_strlen(path[i]));
		is_valid[ft_strlen(path[i])] = '/';
		ft_memcpy(is_valid + ft_strlen(path[i]) + 1, command,
			ft_strlen(command));
		if (access(is_valid, X_OK) == 0)
			return(is_valid);
		free(is_valid);
		i++;
	}
	return (NULL);
}

int	check_absolute(char *command)
{
	int	i;

	i = 0;
	while (command[i])
	{
		if (command[i] == '/')
			break ;
		i++;
	}
	if (command[i] == '\0')
		return (0);
	if (access(command, X_OK) == 0)
		return (1);
	return (0);
}
