/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esezalor <esezalor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 11:32:38 by esezalor          #+#    #+#             */
/*   Updated: 2026/04/08 20:23:49 by esezalor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*envnodes_init(char **envp)
{
	t_env	*env_head;
	t_env	*env_current;
	int		i;

	if (!envp || !envp[0])
		return (NULL); // error handling for when the environment is empty
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
		{
			envclear_allnodes(&env_head);
			return (NULL);
		}
		env_current = env_current->next;
		i++;
	}
	return (env_head);
}

t_env	*env_newnode(char *environment)
{
	t_env	*new_env;

	if (!environment)
		return (NULL);
	new_env = malloc(sizeof(t_env));
	if (!new_env)
		return (NULL);
	new_env->key = fetch_key(environment);
	if (!new_env->key)
		return (free(new_env), NULL);
	if (!find_char(environment, '='))
		new_env->content = NULL;
	else
	{
		new_env->content = fetch_content(environment);
		if (!new_env->content)
			return (free(new_env->key), free(new_env), NULL);
	}
	new_env->next = NULL;
	return (new_env);
}

char	*fetch_key(char *environment)
{
	int		key_len;
	int		i;
	char	*key;

	key_len = 0;
	while (environment[key_len] && environment[key_len] != '='
		&& !(environment[key_len] == '+' && environment[key_len + 1] == '='))
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
	char	*post_key;
	char	*content;

	post_key = ft_strchr(environment, '=');
	if (!post_key)
		return (NULL);
	content = ft_strdup(post_key + 1);
	if (!content)
		return (NULL);
	return (content);
}

char	**envarray_init(t_env *environments)
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
		if (environments->content)
		{
			array[j] = env_join(environments->key, environments->content);
			if (!array[j])
				return ((ft_arrayfree(array)), NULL);
			j++;
		}
		environments = environments->next;
	}
	return (array);
}
