
#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

typedef enum e_type
{
	tk_WORD,
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
	char			**all_paths;
	char			*command_path;
}					t_shell;

// typedef struct s_redir
// {
// 	char			*filename;
// 	enum e_type		*type;
// 	struct s_redir	*next;
// }					t_redir;

// typedef struct s_cmd
// {
// 	char			**cmnd_flags;
// 	int				fd_in;
// 	int				fd_out;
// 	t_redir			*redirect;
// 	struct s_cmd	*next;

// }					t_cmd;

// Environment Initialisation
char				*fetch_key(char *environment);
char				*fetch_content(char *environment);
t_env				*envnodes_init(char **envp);
char				**envarray_init(t_env *environments);
char				*env_fullenv(char *key, char *content);

// Path Initialisation
int					extract_path(t_shell *shell_storage);
int					check_absolute(char *command);
char				*pathfinder(t_shell *storage, char *command);
int	path_ramp(t_shell *storage, char **argv);

// Libft Utils
void				ft_arrayfree(char **str_array, int n);
int					ft_envsize(t_env *lst);

// Environment Utils
void				env_clearnode(t_env **env_lst);
t_env				*env_newnode(char *environment);

#endif