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
	int     status;
	int    	local_fd;

	pid = fork();
	if (pid == -1)
		return (EXIT_FAILURE);
	if (pid == 0)
	{
		if (data->std_in == -1)
		{
			data->std_in = open_file(node->right, "<");
			if (data->std_in == -1)
				return (EXIT_FAILURE);
		}
		else
		{
			local_fd = open_file(node->right, "<");
			if (local_fd == -1)
				return (EXIT_FAILURE);
			dup2(local_fd, STDIN_FILENO);
			close(local_fd);
		}
		if (!node->left->args[0])
		{
			close(data->std_in);
			exit(EXIT_SUCCESS);
		}
		else
		{
			status = execute_ast(node->left, data);
			exit(status);
		}
	}
	waitpid(pid, &status, 0);
	return (WEXITSTATUS(status));
}
