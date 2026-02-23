
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

typedef struct s_redir
{
	char			*filename;
	enum t_type		*type;
	struct s_redir	*next;
}					t_redir;

typedef struct s_cmd
{
	char			**cmnd_flags;
	int				fd_in;
	int				fd_out;
	t_redir			*redirect;
	struct s_cmd	*next;

}					t_cmd;

#endif