/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esezalor <esezalor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 10:26:05 by esezalor          #+#    #+#             */
/*   Updated: 2026/04/09 11:43:31 by esezalor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

typedef struct s_exec	t_exec;
typedef struct s_cmd    t_cmd;
typedef struct s_env    t_env;

// Built-In Initialisation and Basic Built-In Functions
void	built_init(t_exec *storage);
int		is_builtin(t_exec *storage, char *command);
int		exec_builtin(t_exec *storage, t_cmd *cmd_node);
void	builtin_dup(t_exec *storage, t_cmd *cmd_node);
int		ft_echo(t_exec *storage, t_cmd *cmd_node);
int		ft_pwd(t_exec *storage, t_cmd *cmd_node);
int		ft_env(t_exec *storage, t_cmd *cmd_node);
int		ft_exit(t_exec *storage, t_cmd *cmd_node);

// Ft_cd and helpers
int		ft_cd(t_exec *storage, t_cmd *cmd_node);
char	*get_target_path(t_exec *storage, char *command);
char	*cd_path(t_exec *storage, char *key, int size);
int		replace_pwd(t_exec *storage, char *old_pwd);
t_env	*get_envnode(t_exec *storage, char *key, int size);

// Ft_export and helpers
int		ft_export(t_exec *storage, t_cmd *cmd_node);
int		declare_x(t_exec *storage);
int		export_path(t_exec *storage, char *export_var, int valid_key,
			int *env_chg);
int		findnedit(t_exec *storage, char *export_var, int flag);
int		replace_or_append(t_env *current, char *export_var, int flag);
int		valid_export_key(char *export_var);
int		add_path(t_exec *storage, char *export_var);
int		append_export_content(t_env *current, char *export_var);
int		export_error(char *export_var);
int		update_execve_env(t_exec *storage);
void	export_sort(t_env **exp_array, int exp_len);
void	ft_swap(t_env **node1, t_env **node2);
void	print_export(t_env **exp_array);

// Ft_unset and helpers
int		ft_unset(t_exec *storage, t_cmd *cmd_node);
int		valid_unset_key(char *export_var);
int		unset_env(t_exec *storage, char *unset_var, int *env_changed);
int		delete_node(t_env *current, char *unset_var, int var_len);

// Built-In Utils
int		newline_flag(char **command);
int		isvalid_exitcode(char *str);
void	ft_exit_message(char *exit_str);

#endif