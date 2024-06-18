/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmdemirk <dmdemirk@student.42london.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 11:02:00 by dmdemirk          #+#    #+#             */
/*   Updated: 2024/06/17 15:37:05 by dmdemirk         ###   ########.fr       */
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

int execute_ast(t_ast *tree, t_minishell_data *data);
int	execute(t_minishell_data *data);
int	new_process(t_minishell_data *data);

int	execute_ast(t_ast *tree, t_minishell_data *data)
{
	if (tree->type == PIPE)
	{
		printf("PIPE\n");
		// builtin_pipe(tree, data);
	}
	else if (tree->type == PHRASE)
	{
		printf("PHRASE\n");
		data->args = tree->args;
		execute(data);
	}
	else if (tree->type == ENV_VAR)
	{
		printf("ENV_VAR\n");
		//execute_redirect(tree, data);
	}
	else if (tree->type == REDIR_IN)
	{
		printf("REDIR_IN\n");
		//execute_sequence(tree, data);
	}
	else if (tree->type == REDIR_OUT)
	{
		printf("REDIR_OUT\n");
		//execute_sequence(tree, data);
	}
	else if (tree->type == REDIR_APPEND)
	{
		printf("REDIR_APPEND\n");
		//execute_sequence(tree, data);
	}
	else if (tree->type == REDIR_HEREDOC)
	{	
		printf("REDIR_HEREDOC\n");
		//execute_sequence(tree, data);
	}
	return (1);
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
		return (1);
	i = -1;
	while (++i < sizeof(builtin_commands) / sizeof(char *))
		if (ft_strcmp(data->args[0], builtin_commands[i]) == 0)
			return ((*builtin_functions[i])(data));
	return (new_process(data));
}

int	new_process(t_minishell_data *data)
{
	pid_t	pid;
	int		status;
	char	*path;
	char	**envp;

	envp = env_to_array(data->envp);
	path = ft_find_path(data->args[0], data->envp);
	pid = fork();
	if (pid == 0)
	{
		if (execve(path, data->args, envp) == -1)
			perror("minishell");
	}
	else if (pid < 0)
		perror("minishell");
	else
		waitpid(pid, &status, 0);
	return (1);
}
