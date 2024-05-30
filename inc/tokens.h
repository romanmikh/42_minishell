#ifndef TOKENS_H
# define TOKENS_H
# include "../lib/libft/libft.h"


typedef struct s_token {
  char *data;
  struct s_token *next;
} t_token;

#endif
