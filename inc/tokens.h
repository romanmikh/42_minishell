/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmikhayl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 20:53:51 by rmikhayl          #+#    #+#             */
/*   Updated: 2024/06/11 14:59:54 by rocky            ###   ########.fr       */
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
# include "execute.h"
# include "shell.h"
# include "env.h"

# define HISTORY_PATH "./utils/.maxishell_history"

typedef enum e_token_type
{
	PHRASE,
	PIPE,
	ENV_VAR,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC
}	t_token_type;

typedef struct s_token
{
	char			*data;
	t_token_type		type;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

void		add_node(t_token **head, char *str);
void		print_stack(t_token **stack);
void		free_stack(t_token **stack);
int			calc_stack_size(t_token *stack);
char		**list_to_array(t_token *head);
void		build_linked_list(t_token **tokens, char **argv);
void		handle_quotes(char **tokens, int *pos, char **input);
void		handle_special_chars(char **str, t_token **tokens);
void		handle_regular_chars(char **tokens, int *pos, char **input, \
		char *delim);
void		skip_delimiters(char **input, char *delim);
void		reallocate_tokens(char ***tokens, int *bufsize);
void		parse_loop(char **input, char **tokens, int *pos, int *bufsize);
char		**parse_input(char *input);
char		*generate_prompt(t_minishell_data *data);
void		make_history(char *line);
void		cleanup(char *line, char **parsed_text, t_token *tokens, \
		char *prompt);
void		free_minishell_data(t_minishell_data *data);
char		*check_heredoc(char *line);
char		*heredoc(char *eof);
void		init_minishell_data(t_minishell_data *data, char **envp);
void		initialise(int argc, char **argv);
void		execute_command(char **parsed_text, t_token **tokens);
void		print_maxishell(void);
int		input_error_checks(const char *str);
t_token		*tokenise(char *str);
void		print_tokens(t_token *tokens);

#endif
