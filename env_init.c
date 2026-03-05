/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sezalory <sezalory@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 11:32:38 by esezalor          #+#    #+#             */
/*   Updated: 2026/03/05 16:15:44 by sezalory         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*fetch_key(char *environment)
{
	int		key_len;
	int		i;
	char	*key;

	key_len = 0;
	while (environment[key_len] && environment[key_len] != '=')
		key_len++;
	key = ft_calloc(key_len + 1, sizeof(char));
	if (!key)
		return (NULL);
	i = 0;
	while (i < key_len)
	{
		key[i] = environment[i];
		i++;
	}
	return (key);
}

char	*fetch_content(char *environment)
{
	int		post_len;
	char	*post_key;
	char	*content;

	post_key = ft_strchr(environment, '=');
	if (!post_key)
		return (NULL);
	post_len = ft_strlen(post_key);
	content = ft_calloc(post_len, sizeof(char));
	if (!content)
		return (NULL);
	content = ft_strdup(post_key + 1);
	if (!content)
		return (NULL);
	return (content);
}

t_env	*envnodes_init(char **envp)
{
	t_env	*env_head;
	t_env	*env_current;
	int		i;

	env_head = NULL;
	env_current = NULL;
	env_head = env_newnode(envp[0]);
	if (!env_head)
		return (NULL);
	env_current = env_head;
	env_current->next = NULL;
	i = 1;
	while (envp[i])
	{
		env_current->next = env_newnode(envp[i]);
		if (!env_current->next)
			return (env_clearnode(&env_head), NULL);
		env_current = env_current->next;
		i++;
	}
	return (env_head);
}

char	*env_join(char *key, char *content)
{
	char	*variable;
	int		key_len;
	int		content_len;

	key_len = ft_strlen(key);
	content_len = ft_strlen(content);
	variable = ft_calloc(ft_strlen(key) + ft_strlen(content) + 2, sizeof(char));
	if (!variable)
		return (NULL);
	ft_memcpy(variable, key, key_len);
	variable[key_len] = 61;
	ft_memcpy(variable + key_len + 1, content, content_len);
	return (variable);
}

char	**envarray_init(t_exec *storage, t_env *environments)
{
	int		env_amount;
	int		j;
	char	**array;

	env_amount = ft_envsize(environments);
	array = ft_calloc(env_amount + 1, sizeof(char *));
	if (!array)
		return (NULL);
	j = 0;
	while (environments && j < env_amount)
	{
		array[j] = env_join(environments->key, environments->content);
		if (!array[j])
			return ((ft_arrayfree(array, j)), NULL);
		j++;
		environments = environments->next;
	}
	storage->n_env_variables = j;
	return (array);
}
