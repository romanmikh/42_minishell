/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmikhayl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 20:53:51 by rmikhayl          #+#    #+#             */
/*   Updated: 2024/05/31 21:00:07 by rmikhayl         ###   ########.fr       */
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

typedef struct s_token
{
	char			*data;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_AST_node
{
	struct s_AST_node	*left;
	struct s_AST_node	*right;
	char				*value;
	char				*type; // + - * / % // | || & && 
}	t_AST_node;

void		add_node(t_token **head, char *str);
void		print_stack(t_token **stack);
void		free_stack(t_token **stack);
int			calc_stack_size(t_token *stack);
char		**list_to_array(t_token *head);

#endif
