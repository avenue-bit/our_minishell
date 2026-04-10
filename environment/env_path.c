/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esezalor <esezalor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 17:48:46 by esezalor          #+#    #+#             */
/*   Updated: 2026/04/10 19:21:16 by esezalor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headerfiles/minishell.h"

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

	is_valid = NULL;
	if (check_absolute(command) == 1)
		return (ft_strdup(command));
	i = 0;
	while (storage->all_paths && storage->all_paths[i])
	{
		is_valid = ft_calloc(ft_strlen(storage->all_paths[i])
				+ ft_strlen(command) + 2, sizeof(char));
		if (!is_valid)
			break ;
		ft_memcpy(is_valid, storage->all_paths[i],
			ft_strlen(storage->all_paths[i]));
		is_valid[ft_strlen(storage->all_paths[i])] = '/';
		ft_memcpy(is_valid + ft_strlen(storage->all_paths[i]) + 1, command,
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
		return (1);
	return (0);
}
