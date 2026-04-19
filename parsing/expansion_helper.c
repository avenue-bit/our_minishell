/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jille <jille@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 18:01:06 by jille             #+#    #+#             */
/*   Updated: 2026/04/19 18:22:04 by jille            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*append_str(char *dst, const char *src)
{
	size_t	i;
	size_t	j;
	char	*new_str;

	new_str = malloc(ft_strlen(dst) + ft_strlen(src) + 1);
	if (!new_str)
		return (free(dst), NULL);
	i = -1;
	while (dst[++i])
		new_str[i] = dst[i];
	j = 0;
	while (src[j])
		new_str[i++] = src[j++];
	new_str[i] = '\0';
	return (free(dst), new_str);
}

char	*append_char(char *dst, char c)
{
	char	tmp[2];

	tmp[0] = c;
	tmp[1] = '\0';
	return (append_str(dst, tmp));
}

char	*get_env_value(t_env *env, const char *name)
{
	while (env)
	{
		if (ft_strncmp(env->key, name, ft_strlen(name) + 1) == 0)
		{
			if (env->content)
				return (env->content);
			return ("");
		}
		env = env->next;
	}
	return ("");
}

char	*handle_exit_code(char *result, int last_exit, int *i)
{
	char	*code;

	code = ft_itoa(last_exit);
	if (!code)
		return (free(result), NULL);
	result = append_str(result, code);
	free(code);
	if (!result)
		return (NULL);
	*i += 2;
	return (result);
}

char	*handle_variable(char *result, char *in, t_env *env, int *i)
{
	int		beg;
	int		len;
	char	*name;
	char	*value;

	beg = *i + 1;
	len = 0;
	while (in[beg + len] && (ft_isalnum(in[beg + len]) || in[beg + len] == '_'))
		len++;
	name = ft_substr(in, beg, len);
	if (!name)
		return (free(result), NULL);
	value = get_env_value(env, name);
	result = append_str(result, value);
	free(name);
	if (!result)
		return (NULL);
	*i = beg + len;
	return (result);
}
