/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmdemirk <dmdemirk@student.42london.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:32:42 by dmdemirk          #+#    #+#             */
/*   Updated: 2024/09/06 12:28:10 by dmdemirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>
#include "env.h"
#include "exit_status.h"

/*
Functionality:
- Exit the shell
- Free the environment
- Exit with the exit status
 */

void	handle_numeric_error(t_ms_data *data, const char *arg)
{
	exit_status_handler(data, NUMERIC_REQUIRED, ft_strjoin("exit: ", arg));
	exit(NUMERIC_REQUIRED);
}

void	handle_too_many_args_error(t_ms_data *data)
{
	exit_status_handler(data, TOO_MANY_ARGS, "exit");
	exit(TOO_MANY_ARGS);
}

void	handle_exit(t_ms_data *data, int status)
{
	ft_putendl_fd("exit", STDOUT_FILENO);
	data->exit_status = status;
	set_shell_var(&data->shell_variables, "?", ft_itoa(data->exit_status));
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
