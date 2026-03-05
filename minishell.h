
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
	struct s_cmd	*commands;
	char			**execve_env;
	int				n_env_variables;
	char			**all_paths;
	int				n_paths;
	char			*command_path;
	size_t			n_children;
	int				status;
	pid_t			*pids;
	int				pipes[2][2];
}					t_exec;

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

// AdHoc Utils
void				ft_arrayfree(char **str_array, int n);
int					ft_envsize(t_env *lst);
size_t				n_commands(t_cmd *cmd);

// Environment Utils
void				env_clearnode(t_env **env_lst);
t_env				*env_newnode(char *environment);

#endif
