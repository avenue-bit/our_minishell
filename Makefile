NAME = minishell

SRCS = adhoc_utils.c \
		freedom.c \
		main.c \
		signals.c \
		libft_utils/1_libftutils.c \
		libft_utils/2_libftutils.c \
		libft_utils/3_libftutils.c \
		libft_utils/4_libftutils.c \
		libft_utils/ft_printf.c \
		libft_utils/ft_split.c \
		execution/exec_init.c \
		execution/exec_main.c \
		execution/exec_pnf.c \
		execution/exec_redir.c \
		execution/exec_wait.c \
		environment/env_init.c \
		environment/env_path.c \
		environment/env_utils.c \
		builtins/builtins_init.c \
		builtins/ft_basic.c \
		builtins/ft_basic_utils.c \
		builtins/ft_cd.c \
		builtins/ft_export_0.c \
		builtins/ft_export_1.c \
		builtins/ft_export_2.c \
		builtins/ft_unset.c \
		parsing/check_syntax.c \
		parsing/clearing_tkcmd.c \
		parsing/cmd_addrm.c \
		parsing/cmds_init.c \
		parsing/expansion_functions.c \
		parsing/expansion_helper.c \
		parsing/expansion_init.c \
		parsing/heredoc.c \
		parsing/token_init.c \
		print_cmd_tokens.c

OBJS = $(SRCS:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
RLFLAG = -lreadline
HEADERS = headerfiles/minishell.h headerfiles/builtins.h headerfiles/environment.h headerfiles/execution.h headerfiles/libft_utils.h headerfiles/parsing.h

all: $(NAME)

%.o: %.c $(HEADERS) 
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(RLFLAG) -o $(NAME)
	@$ echo MAKE READY, LETS FUCKING GO

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)
	@$ echo CLEAN SLATE BABY

re: fclean all

.PHONY: all clean fclean re