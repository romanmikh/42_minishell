#ifndef TOKENS_H
# define TOKENS_H

typedef struct s_token {
  char *data;
  struct s_token *next;
} t_token;

#endif
