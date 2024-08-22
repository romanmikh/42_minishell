/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmdemirk <dmdemirk@student.42london.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 14:32:40 by dmdemirk          #+#    #+#             */
/*   Updated: 2024/07/11 14:53:27 by dmdemirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include "shell.h"
#include "redirection.h"
#include "execute.h"
#include <string.h>
#include <sys/wait.h>

int	redirect_in(t_ast *node, t_ms_data *data);

/*
   ! FIX
   wc < input.txt - work fine
   wc -l < input.txt - not work (:bad address error)
 */

/**
  - @brief redirection input in context of executing AST
  - 
  - @param node current node in the AST
  - @param data minishell structure data
  - @return status:
  - 0: success
  - 1: error
 */

int	redirect_in(t_ast *node, t_ms_data *data)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (1);
	if (pid == 0)
	{
		data->std_in = open_file(node->right, "<");
		if (data->std_in == -1)
			return (1);
		execute_ast(node->left, data);
		exit(0);
	}
	waitpid(pid, &data->exit_status, 0);
	return (0);
}
