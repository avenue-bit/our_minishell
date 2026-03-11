
#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft_utils/libft_utils.h"
# include <errno.h>
# include <fcntl.h>
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

typedef enum e_type
{
	tk_WORD,
	tk_VAR,
	tk_PIPE,
	tk_REDIR_IN,
	tk_REDIR_OUT,
	tk_HERE_DOC,
	tk_APPEND
}					t_type;

typedef struct s_redir
{
	char			*filename;
	enum e_type		type;
	struct s_redir	*next;
}					t_redir;

typedef struct s_cmd
{
	char			**cmd_flags;
	struct s_redir	*redirections;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_env
{
	char			*key;
	char			*content;
	struct s_env	*next;
}					t_env;

typedef struct s_exec
{
	struct s_env	*environment;
	char			**execve_env;
	int				n_env_variables;
	char			**all_paths;
	int				n_paths;
	char			*command_path;
	int				pre_read_fd;
	int				pipe_fd[2];
	int				exit_code;
	int				last_pid;
}					t_exec;

//********************************************************//
// THIS IS FOR TESTING PURPOSES WHILE JOSH FINISHES WORK
//********************************************************//
t_cmd				*cmdnodes_init(char **argv);
t_cmd				*cmd_newnode(char *command);
void				cmd_clearnode(t_cmd **cmd_lst);
//********************************************************//
// THIS IS FOR TESTING PURPOSES WHILE JOSH FINISHES WORK
//********************************************************//

// Environment Initialisation
char				*fetch_key(char *environment);
char				*fetch_content(char *environment);
t_env				*envnodes_init(char **envp);
char				**envarray_init(t_exec *storage, t_env *environments);
char				*env_join(char *key, char *content);

// Path Initialisation
int					extract_path(t_exec *shell_storage);
int					check_absolute(char *command);
char				*pathfinder(t_exec *storage, char *command);
int					path_ramp(t_exec *storage, char **argv);

// Exec Functions
int					fork_ramp(t_exec *storage, t_cmd *cmd_node);
void				exec_fork(t_exec *storage, t_cmd *cmd_node);
void				child_wrapper(t_exec *storage, t_cmd *current);
void				parent_wrapper(t_exec *storage, t_cmd *current);
void				wait_for_child(t_exec *storage);

// Free Functions
void				path_env_free(t_exec *storage);

// Environment Utils
void				env_clearnode(t_env **env_lst);
t_env				*env_newnode(char *environment);

// Exec Utils
int					is_builtin(char *command);

// AdHoc Utils
void				ft_arrayfree(char **str_array, int n);
int					ft_envsize(t_env *lst);
size_t				n_commands(t_cmd *cmd);

#endif
