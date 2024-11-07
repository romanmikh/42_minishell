/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_out.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmdemirk <dmdemirk@student.42london.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 14:32:59 by dmdemirk          #+#    #+#             */
/*   Updated: 2024/09/09 13:39:13 by dmdemirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include "shell.h"
#include "redirection.h"
#include "execute.h"
#include "pipe.h"
#include <sys/wait.h>

static int	open_and_redirect(t_ast *node, t_ms_data *data);
int			redirect_out(t_ast *node, t_ms_data *data);

/**
  - @brief redirect out ">" to the file output
  - 
  - @param node current node in the AST
  - @param data minishell data structure
  - @return status:
  - 0: success
  - 1: error
 */

/*
   int	redirect_out(t_ast *node, t_ms_data *data)
   {
   pid_t	pid;
   int		status;
   int		fd;

   pid = fork();
   if (pid == -1)
   return (1);
   if (pid == 0)
   {
   if (data->std_out == -1)
   {
   data->std_out = open_file(node->right, ">");
   if (data->std_out == -1)
   return (1);
   }
   else
   {
   fd = open_file(node->right, ">");
   if (fd == -1)
   return (1);
   dup2(fd, STDOUT_FILENO);
   close(fd);
   }
   execute_ast(node->left, data);
   exit(0);
   }
   waitpid(pid, &status, 0);
   return (WEXITSTATUS(status));
   }
 */

static int	open_and_redirect(t_ast *node, t_ms_data *data)
{
	int	fd;

	if (data->std_out == -1)
	{
		data->std_out = open_file(node->right, ">");
		if (data->std_out == -1)
			return (EXIT_FAILURE);
	}
	else
	{
		fd = open_file(node->right, ">");
		if (fd == -1)
			return (EXIT_FAILURE);
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	return (EXIT_SUCCESS);
}

int	redirect_out(t_ast *node, t_ms_data *data)
{
	pid_t	pid;
	int		exec_status;
  int   status;

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
