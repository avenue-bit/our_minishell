/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esezalor <esezalor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 19:44:32 by esezalor          #+#    #+#             */
/*   Updated: 2026/03/24 18:47:27 by esezalor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft_utils/libft_utils.h"
# include <errno.h>
# include <fcntl.h>
# include <linux/limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

# ifndef BOOL
#  define BOOL _Bool
# endif

# ifndef FALSE
#  define FALSE 0
# endif

# ifndef TRUE
#  define TRUE 1
# endif

typedef struct s_exec	t_exec;

typedef enum e_type
{
	tk_WORD,
	tk_VAR,
	tk_PIPE,
	tk_REDIR_IN,
	tk_REDIR_OUT,
	tk_HERE_DOC,
	tk_APPEND
}						t_type;

typedef struct s_token
{
	char				*content;
	t_type				type;
	struct s_token		*next;
	struct s_token		*prev;
}						t_token;

typedef struct s_cmd
{
	char				**cmd_flags;
	char				*infile;
	char				*outfile;
	char				*hd_delim;
	BOOL				append;
	struct s_cmd		*next;
	struct s_cmd		*prev;

}						t_cmd;

typedef struct s_env
{
	char				*key;
	char				*content;
	struct s_env		*next;
}						t_env;

typedef int				(*t_builtin_ptr)(t_exec *, t_cmd *);

typedef struct s_exec
{
	struct s_env		*environment;
	struct s_cmd		*command_nodes;
	struct s_token		*token_nodes;
	char				**execve_env;
	int					n_env_variables;
	char				**all_paths;
	int					n_paths;
	char				*command_path;
	char				*builtins[8];
	t_builtin_ptr		builtin_func[8];
	int					pre_read_fd;
	int					pipe_fd[2];
	int					infile_fd;
	int					outfile_fd;
	int					built_in;
	int					built_out;
	int					exit_code;
	int					last_pid;
}						t_exec;

int						exec_main(t_exec *storage, char **envp, t_cmd *cmd_list,
							t_token *token_lst);
void	exec_main_init(t_exec *storage, t_cmd *cmd_list, t_token *token_lst);
int envnodes_execarray_init(t_exec *storage, char **envp);

// Environment Initialisation
char					*fetch_key(char *environment);
char					*fetch_content(char *environment);
t_env					*envnodes_init(char **envp);
char					**envarray_init(t_exec *storage, t_env *environments);
char					*env_join(char *key, char *content);

// Path Initialisation
int						extract_path(t_exec *shell_storage);
int						check_absolute(char *command);
char					*pathfinder(t_exec *storage, char *command);
int						path_ramp(t_exec *storage, char **argv);

// Path Initialisation
int						extract_path(t_exec *shell_storage);
int						check_absolute(char *command);
char					*pathfinder(t_exec *storage, char *command);
int						path_ramp(t_exec *storage, char **argv);

// Pipe and Fork Functions
int						fork_ramp(t_exec *storage, t_cmd *cmd_node);
void					exec_fork(t_exec *storage, t_cmd *cmd_node);
void					child_wrapper(t_exec *storage, t_cmd *current);
void					parent_wrapper(t_exec *storage, t_cmd *current);
void					wait_for_child(t_exec *storage);

// Redirection Functions
int						infile_outfile_check(t_exec *storage, t_cmd *cmd_node);
int						open_infile(t_exec *storage, t_cmd *cmd_node);
int						open_outfile(t_exec *storage, t_cmd *cmd_node);

// Built-In Initialisation and Basic Built-In Functions
void					built_init(t_exec *storage);
int						is_builtin(t_exec *storage, char *command);
int						exec_builtin(t_exec *storage, t_cmd *cmd_node);
void					builtin_dup(t_exec *storage, t_cmd *cmd_node);
int						ft_echo(t_exec *storage, t_cmd *cmd_node);
int						ft_pwd(t_exec *storage, t_cmd *cmd_node);
int						ft_unset(t_exec *storage, t_cmd *cmd_node);
int						ft_env(t_exec *storage, t_cmd *cmd_node);
int						ft_exit(t_exec *storage, t_cmd *cmd_node);

// Ft_cd and helpers
int						ft_cd(t_exec *storage, t_cmd *cmd_node);
char					*get_target_path(t_exec *storage, char *command);
char					*cd_path(t_exec *storage, char *key, int size);
int						replace_pwd(t_exec *storage, char *old_pwd);
t_env					*get_envnode(t_exec *storage, char *key, int size);

// FT_export and helpers
int						ft_export(t_exec *storage, t_cmd *cmd_node);
int						declare_x(t_exec *storage);
int						export_path(t_exec *storage, char *export_var,
							int valid_key, int *env_chg);
int						findnedit(t_exec *storage, char *export_var, int flag);
int						replace_or_append(t_env *current, char *export_var,
							int flag);
int						valid_export_key(char *export_var);
int						add_path(t_exec *storage, char *export_var);
int						append_export_content(t_env *current, char *export_var);
int						export_error(char *export_var);
int						update_execve_env(t_exec *storage);
void					export_sort(t_env **exp_array, int exp_len);
void					ft_swap(t_env **node1, t_env **node2);
void					print_export(t_env **exp_array);

// Free and Close Functions
void					freeing_ramp(t_exec *storage, int exit_code);
void					path_env_free(t_exec *storage);
void					failexec_close(t_exec *storage);
void					clear_cmds(t_cmd **node);
void					clear_tokens(t_token **tokens);

// Environment Utils
void					env_clearnode(t_env **env_lst);
t_env					*env_newnode(char *environment);

// Built-In Utils
int						newline_flag(char **command);

// AdHoc Utils
void					ft_arrayfree(char **str_array);
int						ft_envsize(t_env *lst);
size_t					n_commands(t_cmd *cmd);
int						find_char(char *str, char c);

#endif
