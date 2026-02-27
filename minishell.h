
#ifndef MINISHELL_H
# define MINISHELL_H

//# include "libft_utils/libft_utils.h"
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

typedef struct s_token
{
	char			*content;
	t_type			type;
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;

typedef struct s_cmd
{
	char			**cmd_flags;
	char			*infile;
	char			*outfile;
	BOOL			append;
	struct s_cmd	*next;
	struct s_cmd	*prev;

}					t_cmd;

typedef struct s_env
{
	char			*key;
	char			*content;
	struct s_env	*next;
}					t_env;

typedef struct s_shell
{
	struct s_env	*environment;
	char			**execve_env;
	int				n_env_variables;
	char			**all_paths;
	int				n_paths;
	char			*command_path;
}					t_shell;

// Environment Initialisation
char				*fetch_key(char *environment);
char				*fetch_content(char *environment);
t_env				*envnodes_init(char **envp);
char				**envarray_init(t_shell *storage, t_env *environments);
char				*env_join(char *key, char *content);

// Path Initialisation
int					extract_path(t_shell *shell_storage);
int					check_absolute(char *command);
char				*pathfinder(t_shell *storage, char *command);
int					path_ramp(t_shell *storage, char **argv);

// Libft Utils
void				ft_arrayfree(char **str_array, int n);
int					ft_envsize(t_env *lst);

// Environment Utils
void				env_clearnode(t_env **env_lst);
t_env				*env_newnode(char *environment);

#endif
