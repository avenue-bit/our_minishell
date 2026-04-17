/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esezalor <esezalor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 10:31:13 by esezalor          #+#    #+#             */
/*   Updated: 2026/04/15 21:07:59 by esezalor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

typedef struct s_exec	t_exec;

typedef struct s_env
{
	char				*key;
	char				*content;
	struct s_env		*next;
}						t_env;

// Environment Initialisation
char					*fetch_key(char *environment);
char					*fetch_content(char *environment);
t_env					*envnodes_init(char **envp);
char					**envarray_init(t_env *environments);
char					*env_join(char *key, char *content);

// Path Initialisation
int						extract_path(t_exec *storage);
int						check_absolute(char *command, int *error1);
char					*pathfinder(t_exec *storage, char *command,
							int *error1);
int						path_ramp(t_exec *storage, char **argv);

// Environment Utils
void					envclear_allnodes(t_env **env_lst);
int						delete_node(t_env *current, char *unset_var,
							int var_len);
t_env					*env_newnode(char *environment);
void					pathfinder_join(char *path, char *is_valid,
							char *command);
int						env_error_paths(char *command, t_exec *storage,
							int error1);

#endif