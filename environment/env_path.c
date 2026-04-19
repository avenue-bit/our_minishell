/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jille <jille@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 17:48:46 by esezalor          #+#    #+#             */
/*   Updated: 2026/04/19 12:17:02 by jille            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	path_ramp(t_exec *storage, char **command)
{
	int	path_error_flag;

	path_error_flag = 0;
	storage->exit_code = check_absolute(command[0], &path_error_flag);
	if (storage->exit_code == 1)
	{
		storage->command_path = ft_strdup(command[0]);
		if (!storage->command_path)
			return (1);
		return (0);
	}
	else if (storage->exit_code > 1)
		return (env_error_paths(command[0], storage, path_error_flag));
	else
	{
		if (extract_path(storage) == -1)
			return (env_error_paths(command[0], storage, path_error_flag));
		storage->command_path = pathfinder(storage, command[0],
				&path_error_flag);
		ft_arrayfree(storage->all_paths);
		storage->all_paths = NULL;
		if (!storage->command_path)
			return (env_error_paths(command[0], storage, path_error_flag));
	}
	return (0);
}

int	check_absolute(char *command, int *path_error_flag)
{
	int			i;
	struct stat	sb;

	i = 0;
	while (command[i])
	{
		if (command[i] == '/')
			break ;
		i++;
	}
	if (command[i] == '\0')
		return (0);
	if (stat(command, &sb) == -1)
		return (127);
	if (S_ISDIR(sb.st_mode))
		return (126);
	else if (access(command, X_OK) == -1)
		return (*path_error_flag = 1, 126);
	return (1);
}

int	extract_path(t_exec *storage)
{
	t_env	*environment;

	environment = storage->environment;
	while (environment)
	{
		if (ft_strncmp(environment->key, "PATH", 5) == 0)
			break ;
		environment = environment->next;
	}
	if (!environment || !environment->content)
		return (storage->exit_code = 127, -1);
	storage->all_paths = ft_split(environment->content, ':');
	if (!storage->all_paths)
		return (storage->exit_code = 1, -1);
	return (0);
}

char	*pathfinder(t_exec *storage, char *command, int *path_error_flag)
{
	int		i;
	char	*is_valid;

	is_valid = NULL;
	i = 0;
	while (storage->all_paths && storage->all_paths[i])
	{
		is_valid = ft_calloc(ft_strlen(storage->all_paths[i])
				+ ft_strlen(command) + 2, sizeof(char));
		if (!is_valid)
			return (storage->exit_code = 1, NULL);
		pathfinder_join(storage->all_paths[i], is_valid, command);
		if (access(is_valid, F_OK) == 0)
		{
			if (access(is_valid, X_OK) == 0)
				return (is_valid);
			else
				return (free(is_valid), *path_error_flag = 1,
					storage->exit_code = 127, NULL);
		}
		free(is_valid);
		is_valid = NULL;
		i++;
	}
	return (*path_error_flag = 1, storage->exit_code = 127, NULL);
}
