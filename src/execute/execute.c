/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmdemirk <dmdemirk@student.42london.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 11:02:00 by dmdemirk          #+#    #+#             */
/*   Updated: 2024/06/03 16:33:53 by dmdemirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "libft.h"
#include <stdio.h>
#include <sys/wait.h>

int	new_process(char **args);

int	execute(char **args)
{
	size_t	i;
	char	*builtin_commands[7];
	int		(*builtin_functions[7])(char **);

	builtin_commands[0] = "cd";
	builtin_commands[1] = "echo";
	builtin_commands[2] = "env";
	builtin_commands[3] = "exit";
	builtin_functions[0] = &builtin_cd;
	builtin_functions[1] = &builtin_echo;
	builtin_functions[2] = &builtin_env;
	builtin_functions[3] = &builtin_exit;
	if (args[0] == NULL)
		return (1);
	i = -1;
	while (++i < sizeof(builtin_commands) / sizeof(char *))
	{
		if (ft_strcmp(args[0], builtin_commands[i]) == 0)
			return ((*builtin_functions[i])(args));
		else
			return (new_process(args));
	}
	return (1);
}

int	new_process(char **args)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		if (execvp(args[0], args) == -1)
			perror("minishell");
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
		perror("minishell");
	else
		waitpid(pid, &status, 0);
	return (1);
}
