/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmikhayl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 20:53:51 by rmikhayl          #+#    #+#             */
/*   Updated: 2024/06/05 17:27:18 by rmikhayl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENS_H
# define TOKENS_H

# include "../lib/libft/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <stdio.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <pwd.h>

# define HISTORY_PATH "./utils/.maxishell_history"

typedef struct s_token
{
	char			*data;
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
void		handle_special_chars(char **tokens, int *pos, char **input);
void		handle_regular_chars(char **tokens, int *pos, char **input, \
		char *delim);
void		skip_delimiters(char **input, char *delim);
void		reallocate_tokens(char ***tokens, int *bufsize);
void		parse_loop(char **input, char **tokens, int *pos, int *bufsize);
char		**parse_input(char *input);
char		*generate_prompt(void);
void		make_history(char *line);
void		cleanup(char *line, char **parsed_text, t_token *tokens);

#endif
