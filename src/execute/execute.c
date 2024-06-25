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

int execution_manager(t_ast *node, t_minishell_data *data);
void execute_tree(t_ast *node, t_minishell_data *data);
int execute_ast(t_ast *node, t_minishell_data *data);
int	execute(t_minishell_data *data);
int	new_process(t_minishell_data *data);

int	execution_manager(t_ast *node, t_minishell_data *data)
{
	// int	i;

	// ft_printf(B_MAG "Executing node with type: %d\n" RESET, node->type);
	// if (node->args)
	// {
	// 	i = 0;
	// 	while (node->args[i])
	// 		ft_printf("  Arg: %s\n", node->args[i++]);
	// }
	execute_ast(node, data);
	return (1);
}

void	execute_tree(t_ast *node, t_minishell_data *data)
{
	// int	i;

	if (!node)
		return ;
	// if (node->left)
	// 	execute_tree(node->left, data);
	// if (node->right)
	// 	execute_tree(node->right, data);
	// ft_printf(B_RED "Calling execution_manager for node type: %d\n" \
	// 	RESET, node->type);
	// if (node->args)
	// {
	// 	i = 0;
	// 	while (node->args[i])
	// 		ft_printf("  Arg: %s\n", node->args[i++]);
	// }
	execution_manager(node, data);
}

int	execute_ast(t_ast *node, t_minishell_data *data)
{
	if (node->type == PIPE)
	{
		printf("PIPE\n");
		builtin_pipe(node, data);
	}
	else if (node->type == PHRASE)
	{
		printf("PHRASE\n");
		data->args = node->args;
		execute(data);
	}
	else if (node->type == ENV_VAR)
	{
		printf("ENV_VAR\n");
		//execute_redirect(node, data);
	}
	else if (node->type == REDIR_IN)
	{
		printf("REDIR_IN\n");
		//execute_sequence(node, data);
	}
	else if (node->type == REDIR_OUT)
	{
		printf("REDIR_OUT\n");
		//execute_sequence(node, data);
	}
	else if (node->type == REDIR_APPEND)
	{
		printf("REDIR_APPEND\n");
		//execute_sequence(node, data);
	}
	else if (node->type == REDIR_HEREDOC)
	{	
		printf("REDIR_HEREDOC\n");
		//execute_sequence(node, data);
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
    char	*path;
    char	**envp;
    pid_t pid;
	int fd[2];

    envp = env_to_array(data->envp);
    path = ft_find_path(data->args[0], data->envp);

	pipe(fd);
    pid = fork();
    if (pid == -1)
		ft_perror("fork");
    if (pid == 0)
    {
		dup2(fd[0], STDIN_FILENO);
		close_fds(fd);
        if(execve(path, data->args, envp) == -1)
            perror("minishell");
        exit(EXIT_FAILURE);
    }
	close_fds(fd);
	waitpid(pid, NULL, 0);
    return (1);
}