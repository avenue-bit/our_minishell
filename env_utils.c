/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esezalor <esezalor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 18:10:11 by esezalor          #+#    #+#             */
/*   Updated: 2026/02/24 18:13:30 by esezalor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_clearnode(t_env **env_lst)
{
	t_env	*current_node;
	t_env	*next_node;

	if (!*env_lst)
		return ;
	current_node = *env_lst;
	while (current_node)
	{
		next_node = current_node->next;
		free(current_node->key);
		free(current_node->content);
		free(current_node);
		current_node = next_node;
	}
	*env_lst = NULL;
}

t_env	*env_newnode(char *environment)
{
	t_env *new_env;

	new_env = malloc(sizeof(t_env));
	if (!new_env)
		return (NULL);
	new_env->key = fetch_key(environment);
	new_env->content = fetch_content(environment);
	new_env->next = NULL;
	return (new_env);
}