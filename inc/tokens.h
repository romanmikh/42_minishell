/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmikhayl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 20:53:51 by rmikhayl          #+#    #+#             */
/*   Updated: 2024/09/06 12:29:14 by dmdemirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENS_H
# define TOKENS_H

# include "../lib/libft/inc/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <stdio.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <pwd.h>
# include "shell.h"
# include "env.h"

# define HISTORY_PATH "./src/utils/.maxishell_history"

typedef enum e_token_type
{
	PHRASE,
	PIPE,
	ENV_VAR,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC,
	NONE
}	t_token_type;

typedef struct s_token
{
	t_token_type			type;
	char					*data;
	struct s_token			*next;
	struct s_token			*prev;
}	t_token;

typedef struct s_ast
{
	t_token_type		type;
	char				**args;
	struct s_ast		*left;
	struct s_ast		*right;
}	t_ast;

typedef struct s_loop_data
{
	char	*prompt;
	char	*input;
	char	*trimmed_input;
	t_token	*tokens;
	t_ast	*tree;
}	t_loop_data;

void		final_quote_removal(int arg_count, t_ast *command_node);
char		*expand_env_var(char *arg, t_ms_data *data);
void		post_process_command_args(t_ast *command_node, int arg_count, \
		t_ms_data *data);
void		add_node(t_token **head, char *str);
void		print_stack(t_token **stack);
void		free_stack(t_token **stack);
int			calc_stack_size(t_token *stack);
char		**list_to_array(t_token *head);
void		build_linked_list(t_token **tokens, char **argv);
void		handle_quotes(char **tokens, int *pos, char **input);
char		*handle_special_chars(char *str, t_token **tokens);
void		skip_delimiters(char **input, char *delim);
void		reallocate_tokens(char ***tokens, int *bufsize);
void		parse_loop(char **input, char **tokens, int *pos, int *bufsize);
char		**parse_input(char *input);
char		*generate_prompt(t_ms_data *data);
void		make_history(char *line);
void		loop_cleanup(t_loop_data *loop_data, t_token *tokens_head);
void		free_ms_data(t_ms_data *data);
char		*check_heredoc(char *line);
char		*heredoc(char *eof);
void		init_ms_data(t_ms_data *data, char **argv, char **envp);
void		initialise(int argc, char **argv);
void		execute_command(char **parsed_text, t_token **tokens);
void		print_maxishell(void);
int			input_error_checks(t_loop_data *loop_data);
t_token		*tokenise(char *str);
void		print_tokens(t_token *tokens);
t_ast		*parse_tokens(t_token **tokens, t_ms_data *data);
void		print_tokens(t_token *tokens);
void		visualize_ast(t_ast *root);
void		free_ast(t_ast *node);
void		free_all_tokens(t_token *tokens);
t_token		*new_token(char *value, t_token_type type);
void		append_token(t_token **tokens, t_token *new_token);
int			valid_operator(const char **str);
t_ast		*new_ast_node(void);
t_ast		*create_redir(t_token **tokens, t_token *tmp, t_ms_data *data);
int			arg_len(t_token *current);
void		set_command_args(t_ast *command_node, t_token **tokens, \
				int arg_count);
t_ast		*manage_commands(t_token **tokens, t_ms_data *data);
t_ast		*create_redir_node(t_token *token);
int			is_redir_node(t_token *tokens);
t_ast		*manage_redirs(t_token **tokens, t_ms_data *data);
t_ast		*manage_pipe(t_token **tokens, t_ms_data *data);
char		*trim_input(char *str);
void		print_ast_root(t_ast *root);
void		execute_tree(t_ast *node, t_ms_data *data);
char		*expand_env_and_loc_var(char *arg, t_ms_data *data);
char		*append_literal(char **start, char *processed_arg);
char		*process_argument(char *arg, t_ms_data *data);
char		*expand_variable(char **start, t_ms_data *data);
void		clear_history_file(void);
int			is_in_single_quotes(char *arg);
void		print_ast_args(t_ast *node);
void		append_word_if_valid(char *start, char *str, t_token **tokens);
char		*exit_status_adj(char *arg);
char		*str_start_adj(char *arg);
char		*tmp_adj(char *arg);
int			cmd_arg_len(t_token *current);
char		*exit_status_adj(char *arg);
int			is_in_single_quotes(char *arg);
char		*str_start_adj(char *arg);
char		*tmp_adj(char *arg);
char		*append_literal(char **start, char *processed_arg);
char		*expand_variable(char **start, t_ms_data *data);
char		*expand_env_and_loc_var(char *arg, t_ms_data *data);
void		final_quote_removal(int arg_count, t_ast *command_node);

#endif