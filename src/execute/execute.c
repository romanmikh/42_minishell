/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmdemirk <dmdemirk@student.42london.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 11:02:00 by dmdemirk          #+#    #+#             */
/*   Updated: 2024/07/11 18:42:17 by dmdemirk         ###   ########.fr       */
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

int			execute_ast(t_ast *node, t_ms_data *data);
static int	execute(t_ms_data *data);
static int	new_process(t_ms_data *data);

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
		return (1);
	if (node->type == PIPE)
		return (builtin_pipe(node, data));
	else if (node->type == ENV_VAR)
		ft_printf(BLU"ENV_VAR\n"RESET);
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
	return (0);
}

/**
  - @brief execute distribution function
  - 
  - @param data minishell data struct
  - @return int return status:
  - 				- 0: success	
  - 				- 1: error
 */

static int	execute(t_ms_data *data)
{
	size_t	i;
	char	*builtin_commands[7];
	int		(*builtin_functions[7])(t_ms_data *);

	builtin_commands[0] = "cd";
	builtin_commands[1] = "echo";
	builtin_commands[2] = "env";
	builtin_commands[3] = "exit";
	builtin_commands[4] = "export";
	builtin_commands[5] = "pwd";
	builtin_commands[6] = "unset";
	builtin_functions[0] = &builtin_cd;
	builtin_functions[1] = &builtin_echo;
	builtin_functions[2] = &builtin_env;
	builtin_functions[3] = &builtin_exit;
	builtin_functions[4] = &builtin_export;
	builtin_functions[5] = &builtin_pwd;
	builtin_functions[6] = &builtin_unset;
	if (data->args[0] == NULL)
		ft_perror("minishel");
	i = -1;
	while (++i < sizeof(builtin_commands) / sizeof(char *))
		if (ft_strcmp(data->args[0], builtin_commands[i]) == 0)
			return ((*builtin_functions[i])(data));
	return (new_process(data));
}

/**
  - @brief executes a new process
  - 
  - @param data minishell data structure
  - @return int return status:
  - 				- 0: success	
  - 				- 1: error
 */

static int	new_process(t_ms_data *data)
{
	pid_t	pid;

	if (data->std_in == -1)
		data->std_in = dup(STDIN_FILENO);
	if (data->std_out == -1)
		data->std_out = dup(STDOUT_FILENO);
	pid = fork();
	if (pid == -1)
		ft_perror("fork");
	if (pid == 0)
	{
		if (data->std_in != -1)
			dup2(data->std_in, STDIN_FILENO);
		if (data->std_out != -1)
			dup2(data->std_out, STDOUT_FILENO);
		close_fds(data->std_in, data->std_out);
		if (execve(ft_find_path(data->args[0], data->envp), \
					data->args, env_to_array(data->envp)) == -1)
			ft_perror("minishell");
	}
	close_fds(data->std_in, data->std_out);
	waitpid(pid, &data->exit_status, 0);
	return (0);
}
