/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esezalor <esezalor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 11:32:38 by esezalor          #+#    #+#             */
/*   Updated: 2026/02/24 13:00:38 by esezalor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*fetch_key(char *environment)
{
	int		len;
	int		post_len;
	int		trim_len;
	int		i;
	char	*key;

	len = ft_strlen(environment);
	post_len = ft_strlen(ft_strchr(environment, 61));
	trim_len = len - post_len;
	key = calloc(trim_len + 1, sizeof(char));
	if (!key)
		return (NULL);
	i = 0;
	while (i < trim_len)
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
	int		i;

	post_key = ft_strchr(environment, 61);
	post_len = ft_strlen(post_key);
	content = calloc(post_len, sizeof(char));
	if (!content)
		return (NULL);
	i = 0;
	while (i < post_len)
	{
		content[i] = post_key[i + 1];
		i++;
	}
	return (content);
}

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
	t_env	*new_env;

	new_env = malloc(sizeof(t_env));
	if (!new_env)
		return (NULL);
	new_env->key = fetch_key(environment);
	new_env->content = fetch_content(environment);
	new_env->next = NULL;
	return (new_env);
}

int	main(int argc, char **argv, char **envp)
{
	t_env	*env_head;
	t_env	*env_tail;
	int		i;

	env_head = NULL;
	env_tail = NULL;
	env_head = env_newnode(envp[0]);
	if (!env_head)
		return (env_clearnode(env_head), 0);
	env_tail = env_head;
	env_tail->next = NULL;
	i = 1;
	while (envp[i])
	{
		env_tail->next = env_newnode(envp[i]);
		if (!env_tail->next)
			return (env_clearnode(&env_head), 0);
		env_tail = env_tail->next;
		i++;
	}
	return (0);
}
