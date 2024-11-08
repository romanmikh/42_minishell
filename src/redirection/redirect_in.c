/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmdemirk <dmdemirk@student.42london.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 14:32:40 by dmdemirk          #+#    #+#             */
/*   Updated: 2024/11/08 13:14:21 by dmdemirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include "shell.h"
#include "redirection.h"
#include "execute.h"
#include <string.h>
#include <sys/wait.h>

int	redirect_in(t_ast *node, t_ms_data *data);

static int	setup_redirection(t_ast *node, int *original_stdin)
{
	int	fd;

	*original_stdin = dup(STDIN_FILENO);
	if (*original_stdin == -1)
		return (-1);
	fd = open_file(node->right, "<");
	if (fd == -1)
	{
		close(*original_stdin);
		return (-1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		close(fd);
		close(*original_stdin);
		return (-1);
	}
	close(fd);
	return (EXIT_SUCCESS);
}

int	redirect_in(t_ast *node, t_ms_data *data)
{
	int	status;
	int	original_stdin;

	if (setup_redirection(node, &original_stdin) == -1)
		return (EXIT_FAILURE);
	if (!node->left->args[0])
		status = EXIT_SUCCESS;
	else
		status = execute_ast(node->left, data);
	if (dup2(original_stdin, STDIN_FILENO) == -1)
		status = EXIT_FAILURE;
	close(original_stdin);
	return (status);
}
