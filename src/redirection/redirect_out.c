/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_out.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmdemirk <dmdemirk@student.42london.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 14:32:59 by dmdemirk          #+#    #+#             */
/*   Updated: 2024/07/11 14:52:28 by dmdemirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include "shell.h"
#include "redirection.h"
#include "execute.h"
#include "pipe.h"
#include <sys/wait.h>

int	redirect_out(t_ast *node, t_ms_data *data);

/**
  - @brief redirect out ">" to the file output
  - 
  - @param node current node in the AST
  - @param data minishell data structure
  - @return status:
  - 0: success
  - 1: error
 */

int	redirect_out(t_ast *node, t_ms_data *data)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		return (1);
	if (pid == 0)
	{
		data->std_out = open_file(node->right, ">");
		if (data->std_out == -1)
			return (1);
		execute_ast(node->left, data);
		exit(0);
	}
	waitpid(pid, &status, 0);
	return (WEXITSTATUS(status));
}
