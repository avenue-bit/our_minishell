/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esezalor <esezalor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 19:44:32 by esezalor          #+#    #+#             */
/*   Updated: 2026/04/10 19:15:14 by esezalor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define _POSIX_SOURCE
# define _DEFAULT_SOURCE

# include "./builtins.h"
# include "./environment.h"
# include "./execution.h"
# include "./libft_utils.h"
# include "./parsing.h"
# include <errno.h>
# include <fcntl.h>
# include <linux/limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/ioctl.h>
# include <sys/wait.h>
# include <unistd.h>

extern volatile __sig_atomic_t	g_signal;

# ifndef BOOL
#  define BOOL _Bool
# endif

# ifndef FALSE
#  define FALSE 0
# endif

# ifndef TRUE
#  define TRUE 1
# endif

typedef struct s_exec			t_exec;

typedef enum e_type
{
	tk_WORD,
	tk_VAR,
	tk_PIPE,
	tk_REDIR_IN,
	tk_REDIR_OUT,
	tk_HERE_DOC,
	tk_APPEND
}								t_type;

typedef struct s_token
{
	char						*content;
	t_type						type;
	struct s_token				*next;
	struct s_token				*prev;
}								t_token;

typedef struct s_cmd
{
	char						**cmd_flags;
	char						*infile;
	char						*outfile;
	char						*heredoc_delim;
	BOOL						append;
	struct s_cmd				*next;
	struct s_cmd				*prev;

}								t_cmd;

typedef int						(*t_builtin_ptr)(t_exec *, t_cmd *);

typedef struct s_exec
{
	struct s_token				*token_nodes;
	struct s_cmd				*command_nodes;
	int							n_commands_nodes;
	struct s_env				*environment;
	char						**execve_env;
	char						**all_paths;
	char						*command_path;
	pid_t						*c_pids;
	int							pre_read_fd;
	int							pipe_fd[2];
	int							infile_fd;
	int							outfile_fd;
	t_builtin_ptr				builtin_func[8];
	char						*builtins[8];
	int							built_in;
	int							built_out;
	int							exit_code;
	int							exit_flag;
}								t_exec;

// Free and Close Functions
void							freeing_ramp(t_exec *storage);
void							clear_cmds(t_cmd **node);
void							clear_tokens(t_token **tokens);
void							free_in_readline(t_exec *storage);
void							unlink_files(t_cmd *cmds);
void							free_out_readline(t_exec *storage);
void							failexec_close(t_exec *storage);

// Signals
void							sh_global(int signum);
int								sh_readline_hook(void);
void							config_interactive_sigs(void);
void							config_child_ign(void);
void							config_child_dfl(void);

// AdHoc Utils
void							ft_arrayfree(char **str_array);
int								ft_envsize(t_env *lst);
size_t							n_commands(t_cmd *cmd);
int								find_char(char *str, char c);

#endif
