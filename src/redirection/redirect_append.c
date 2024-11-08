/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_append.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmdemirk <dmdemirk@student.42london.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 15:13:15 by dmdemirk          #+#    #+#             */
/*   Updated: 2024/11/08 15:13:40 by dmdemirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include "shell.h"
#include "redirection.h"
#include "execute.h"
#include "pipe.h"
#include <sys/wait.h>

static int	open_and_redirect(t_ast *node, t_ms_data *data)
{
	int	fd;

	if (data->std_out == -1)
	{
		data->std_out = open_file(node->right, ">>");
		if (data->std_out == -1)
			return (EXIT_FAILURE);
	}
	else
	{
		fd = open_file(node->right, ">>");
		if (fd == -1)
			return (EXIT_FAILURE);
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	return (EXIT_SUCCESS);
}

int	redirect_append(t_ast *node, t_ms_data *data)
{
	pid_t	pid;
	int		exec_status;
	int		status;

	pid = fork();
	if (pid == -1)
		return (EXIT_FAILURE);
	if (pid == 0)
	{
		if (open_and_redirect(node, data) != 0)
			exit(EXIT_FAILURE);
		exec_status = execute_ast(node->left, data);
		exit(exec_status);
	}
	if (waitpid(pid, &status, 0) == -1)
		return (EXIT_FAILURE);
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (WEXITSTATUS(status));
}
