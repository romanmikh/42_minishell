/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmdemirk <dmdemirk@student.42london.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 11:02:00 by dmdemirk          #+#    #+#             */
/*   Updated: 2024/09/09 12:54:44 by dmdemirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "libft.h"
#include <stdio.h>
#include <sys/wait.h>
#include "shell.h"
#include "execute.h"
#include "tokens.h"
#include "pipe.h"
#include "redirection.h"
#include "exit_status.h"
#include "signals.h"
#import "exit_status.h"

int			execute_ast(t_ast *node, t_ms_data *data);

/**
  - @brief execute Abstract Syntax Tree
  - 
  - @param node Abstract Syntax Tree Node
  - @param data minishell data struct
  - @return int return status:
  - 				- 0: success	
  - 				- 1: error
 */

int	execute_ast(t_ast *node, t_ms_data *data)
{
	if (!node)
		return (EXIT_FAILURE);
	if (node->type == PIPE)
		return (builtin_pipe(node, data));
	else if (node->type == REDIR_IN)
		return (redirect_in(node, data));
	else if (node->type == REDIR_OUT)
		return (redirect_out(node, data));
	else if (node->type == REDIR_APPEND)
		return (redirect_append(node, data));
	else if (node->type == REDIR_HEREDOC)
		return (redirect_here_doc(node, data));
	else if (node->type == PHRASE)
	{
		data->args = node->args;
		return (execute(data));
	}
	return (EXIT_SUCCESS);
}