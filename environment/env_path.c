/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esezalor <esezalor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 17:48:46 by esezalor          #+#    #+#             */
/*   Updated: 2026/04/09 11:24:56 by esezalor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headerfiles/minishell.h"

// 1. extract_path: Look for the Key "PATH" inside the environment list,
// extract, split and store each path in a string array stored in shell storage

// 2. pathfinder: Based on given command[1] append to each path and check if executable
// return fully appended '/ + cmd' string of path

int	path_ramp(t_exec *storage, char **command)
{
	if (extract_path(storage) == -1)
		return (-1);
	storage->command_path = pathfinder(storage, command[0]);
	ft_arrayfree(storage->all_paths);
	storage->all_paths = NULL;
	if (!storage->command_path)
		return (-1);
	return (0);
}

int	extract_path(t_exec *shell_storage)
{
	t_env	*environment;

	environment = shell_storage->environment;
	while (environment)
	{
		if (ft_strncmp(environment->key, "PATH", 5) == 0)
			break ;
		environment = environment->next;
	}
	if (!environment || !environment->content)
		return (-1);
	shell_storage->all_paths = ft_split(environment->content, ':');
	if (!shell_storage->all_paths)
		return (-1);
	return (0);
}

char	*pathfinder(t_exec *storage, char *command)
{
	int		i;
	char	*is_valid;
	char	**path;

	is_valid = NULL;
	if (check_absolute(command) == 1)
		return (ft_strdup(command));
	path = storage->all_paths;
	i = 0;
	while (path && path[i])
	{
		is_valid = ft_calloc(ft_strlen(path[i]) + ft_strlen(command) + 2,
				sizeof(char));
		if (!is_valid)
			break ;
		ft_memcpy(is_valid, path[i], ft_strlen(path[i]));
		is_valid[ft_strlen(path[i])] = '/';
		ft_memcpy(is_valid + ft_strlen(path[i]) + 1, command,
			ft_strlen(command));
		if (access(is_valid, X_OK) == 0)
			return (is_valid);
		free(is_valid);
		is_valid = NULL;
		i++;
	}
	return (free(is_valid), NULL);
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
		return (1); // errno needed for failure of access
	return (0);
}
