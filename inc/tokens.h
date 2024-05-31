#ifndef TOKENS_H
# define TOKENS_H
# include "../lib/libft/libft.h"

typedef struct s_token {
  char *data;
  struct s_token *next;
} t_token;

typedef struct s_AST_node {
  struct s_AST_node *left;
  struct s_AST_node *right;
  char *value;
  char *type; // + - * / % // | || & && 
} s_AST_node;

void	add_node(t_token **head, char *str);
void	print_stack(t_token **stack);
void	free_stack(t_token **stack);

#endif
