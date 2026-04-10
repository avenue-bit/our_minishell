/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jille <jille@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 18:51:10 by jille             #+#    #+#             */
/*   Updated: 2026/04/10 18:51:13 by jille            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

typedef enum e_type		t_type;

typedef struct s_token	t_token;

void					clear_tokens(t_token **tokens);
void					clear_cmds(t_cmd **node);

int						add_token_node(t_token **tokens, char *content,
							t_type type);
int						handle_words(char *input, t_token **tokens);
int						create_tokens(char *inp, t_token **tokens, int check,
							int i);
int						count_tokens_words(t_token *tokens);

int						fill_cmd_data_redir(t_token **tokens, t_cmd *cmd);
int						fill_node_data(t_token **tokens, t_cmd *cmd, int *i);
int						fill_cmd_data(t_token **tokens, t_cmd *cmd);
t_cmd					*init_new_cmd(t_cmd **cmd_list, t_token *tokens);
void					create_cmd_list(t_cmd **cmd_list, t_token *tokens);

t_cmd					*add_cmd_node(t_cmd **cmd_list);
void					remove_last_cmd_node(t_cmd **cmd_list, t_cmd *node);
int						set_redir_path(t_cmd *cmd, t_token **tokens,
							t_type type);

int						check_redirection(t_type type);
int						print_syntax_error(char *token);
int						check_syntax(t_token *tokens);

int						process_heredoc(t_token *tokens, t_cmd *cmd);
char					*create_heredoc_file_name(int num);
void					heredoc_loop(t_cmd **cmd, int h_fd);
int						heredoc_to_file(t_cmd **cmd);

char					*append_str(char *dst, const char *src);
char					*append_char(char *dst, char c);
char					*get_env_value(t_env *env, const char *name);
char					*handle_exit_code(char *result, int last_exit, int *i);
char					*handle_variable(char *result, char *input, t_env *env,
							int *i);

char					*append_and_advance(char *str, char c, int *i);
char					*handle_dollar_case(char *str, char *input,
							t_exec *storage, int *i);
char					*handle_quote_case(char *str, char *input, int *i,
							char *quote);
char					*process_expansion(char *input, t_exec *storage);

char					*remove_quotes(t_token *tokens);

void					expand_variables(t_token **tokens, t_exec *storage);

#endif