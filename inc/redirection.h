#ifndef REDIRECTION_H
# define REDIRECTION_H

#include "shell.h"
#include "tokens.h"

/*  redirect_in */
int	redirect_in(t_ast *node, t_minishell_data *data);
int redirect_out(t_ast *node, t_minishell_data *data);

/*  utils   */
int open_file(t_ast *node, char *direction);
// void redirect(t_minishell_data *data, int fd, char *direction);
// int execute_redirection(t_ast *node, t_minishell_data *data);

#endif