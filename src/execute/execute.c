/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmdemirk <dmdemirk@student.42london.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 11:02:00 by dmdemirk          #+#    #+#             */
/*   Updated: 2024/06/26 15:27:32 by dmdemirk         ###   ########.fr       */
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

/*
	REFACTORING HERE
*/

int	execute_ast(t_ast *node, t_minishell_data *data);
int	execute(t_minishell_data *data);
int	new_process(t_minishell_data *data);

int	execute_ast(t_ast *node, t_minishell_data *data)
{
	if (!node)
		return (1);
	if (node->type == PIPE)
	{
		printf(RED"PIPE\n"RESET);
		return (builtin_pipe(node, data));
	}
	else if (node->type == ENV_VAR) 	// "$()"
	{
		printf(BLU"ENV_VAR\n"RESET);
		//execute_redirect(node, data);
	}
	else if (node->type == REDIR_IN)
	{
		printf(GRN"REDIR_IN\n"RESET);
		return (redirect_in(node, data));
	}
	else if (node->type == REDIR_OUT)	// ">"
	{
		printf(CYA"REDIR_OUT\n"RESET);
		return (redirect_out(node, data));
	}
	else if (node->type == REDIR_APPEND) // ">>"
	{
		printf(CYA"REDIR_APPEND\n"RESET);
		//execute_sequence(node, data);
	}
	else if (node->type == REDIR_HEREDOC) // "<<"
	{
		printf(MAG"REDIR_HEREDOC\n"RESET);
		//execute_sequence(node, data);
	}
	else if (node->type == PHRASE)
	{
		printf(YEL"PHRASE\n"RESET);
		data->args = node->args;
		return (execute(data));
	}
	return (0);
}

int	execute(t_minishell_data *data)
{
	size_t	i;
	char	*builtin_commands[7];
	int		(*builtin_functions[7])(t_minishell_data *);

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
		return (2);
	i = -1;
	while (++i < sizeof(builtin_commands) / sizeof(char *))
		if (ft_strcmp(data->args[0], builtin_commands[i]) == 0)
			return ((*builtin_functions[i])(data));
	return (new_process(data));
}

int	new_process(t_minishell_data *data)
{
	char	*path;
	char	**envp;
	pid_t	pid;

	envp = env_to_array(data->envp);
	path = ft_find_path(data->args[0], data->envp);
	pid = fork();
	if (pid == -1)
		ft_perror("fork");
	if (pid == 0)
	{
		if (data->temp_fd != -1)
		{
			dup2(data->temp_fd, STDIN_FILENO);
			close(data->temp_fd);
		}
		if (data->temp_fd == 1)
		{
			dup2(data->temp_fd, STDOUT_FILENO);
			close(data->temp_fd);
		}
		if (execve(path, data->args, envp) == -1)
			ft_perror("minishell");
	}
	waitpid(pid, NULL, 0);
	free(path);
	ft_free_2d_arr(envp);
	return (0);
}
