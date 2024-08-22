/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmdemirk <dmdemirk@student.42london.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 11:04:39 by dmdemirk          #+#    #+#             */
/*   Updated: 2024/06/26 14:47:46 by dmdemirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include <unistd.h>
#include "libft.h"
#include "execute.h"
#include <stdio.h>
#include <sys/wait.h>
#include "pipe.h"

int		builtin_pipe(t_ast *node, t_ms_data *data);
pid_t	execute_child(t_ast *node, t_ms_data *data, \
			int fd[2], int direction);

/**
- @brief execute pipe when | is found in the command
- 
- @param node current node in the AST
- @param data minishell structure data
- @return int return status:
- 				- 0: success
- 				- 1: error
 */

int	builtin_pipe(t_ast *node, t_ms_data *data)
{
	int		fd[2];
	pid_t	pid_1;
	pid_t	pid_2;
	int		status;

	pid_2 = -1;
	if (pipe(fd) == -1)
		ft_perror("pipe");
	pid_1 = execute_child(node->left, data, fd, 0);
	if (node->right != NULL)
		pid_2 = execute_child(node->right, data, fd, 1);
	else
	{
		close(fd[1]);
		data->std_in = fd[0];
		return (WAIT_NEXT_COMMAND);
	}
	close_fds(fd[0], fd[1]);
	if (pid_1 > 0)
		waitpid(pid_1, &status, 0);
	if (node->right != NULL && pid_2 > 0)
		waitpid(pid_2, &status, 0);
	return (WEXITSTATUS(status));
}

/**
- @brief execute child process in the pipe context
- @param node current node in the AST
- @param data minishell structure data
- @param fd file descriptors
- @param direction direction of the pipe if 0 - node_left, if 1 - node_right
- @return pid_t return the process id
 */

pid_t	execute_child(t_ast *node, t_ms_data *data, \
			int fd[2], int direction)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		ft_perror("fork");
	if (pid == 0)
	{
		if (direction == 0)
			dup2(fd[1], STDOUT_FILENO);
		else
			dup2(fd[0], STDIN_FILENO);
		close_fds(fd[0], fd[1]);
		execute_ast(node, data);
		exit(EXIT_SUCCESS);
	}
	return (pid);
}
