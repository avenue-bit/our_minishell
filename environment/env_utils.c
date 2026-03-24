/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esezalor <esezalor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 18:10:11 by esezalor          #+#    #+#             */
/*   Updated: 2026/03/24 18:51:14 by esezalor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

char	*env_join(char *key, char *content)
{
	char *variable;
	int key_len;
	int content_len;

	key_len = ft_strlen(key);
	content_len = ft_strlen(content);
	variable = ft_calloc(key_len + content_len + 2, sizeof(char));
	if (!variable)
		return (NULL);
	ft_memcpy(variable, key, key_len);
	variable[key_len] = 61;
	ft_memcpy(variable + key_len + 1, content, content_len);
	return (variable);
}
