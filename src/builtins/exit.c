/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmdemirk <dmdemirk@student.42london.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:32:42 by dmdemirk          #+#    #+#             */
/*   Updated: 2024/09/09 13:10:47 by dmdemirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>
#include "env.h"
#include "exit_status.h"
#include "tokens.h"

/*
Functionality:
- Exit the shell
- Free the environment
- Exit with the exit status
 */

void	clear_history_file(void)
{
	remove(HISTORY_PATH);
}

void	handle_numeric_error(t_ms_data *data, const char *arg)
{
	char	*temp_str;

	temp_str = ft_strjoin("exit: ", arg);
	exit_status_handler(data, NUMERIC_REQUIRED, temp_str);
	exit(NUMERIC_REQUIRED);
}

void	handle_too_many_args_error(t_ms_data *data)
{
	exit_status_handler(data, TOO_MANY_ARGS, "exit");
	exit(TOO_MANY_ARGS);
}

void	handle_exit(t_ms_data *data, int status)
{
	char	*exit_status_str;

	ft_putendl_fd("exit", STDOUT_FILENO);
	data->exit_status = status;
	exit_status_str = ft_itoa(data->exit_status);
	set_shell_var(&data->shell_variables, "?", exit_status_str);
	free(exit_status_str);
	clear_history_file();
	free_ms_data(data);
	exit(status);
}

int	builtin_exit(t_ms_data *data)
{
	int	number;

	number = 0;
	if (data->args[1])
	{
		if (ft_isnumber(data->args[1]) == 0)
			handle_numeric_error(data, data->args[1]);
		else if (data->args[2])
			handle_too_many_args_error(data);
		else
		{
			number = ft_atoi(data->args[1]);
			handle_exit(data, number);
		}
	}
	else
		handle_exit(data, 0);
	return (0);
}
