/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmdemirk <dmdemirk@student.42london.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 14:32:40 by dmdemirk          #+#    #+#             */
/*   Updated: 2024/11/07 19:40:50 by dmdemirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include "shell.h"
#include "redirection.h"
#include "execute.h"
#include <string.h>
#include <sys/wait.h>

int	redirect_in(t_ast *node, t_ms_data *data);

static int	handle_child_process(t_ast *node, t_ms_data *data)
{
	int	local_fd;
	int	status;

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
	status = execute_ast(node->left, data);
	exit(status);
}

int	redirect_in(t_ast *node, t_ms_data *data)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		return (EXIT_FAILURE);
	if (pid == 0)
		handle_child_process(node, data);
	waitpid(pid, &status, 0);
	return (WEXITSTATUS(status));
}
