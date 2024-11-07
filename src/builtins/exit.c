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
#include "signals.h"
#include "builtins.h"

/*
Functionality:
- Exit the shell
- Free the environment
- Exit with the exit status
 */

void	cleanup_exit_resources(t_ms_data *data)
{
	if (data->args)
	{
		ft_free_2d_arr(data->args);
		data->args = NULL;
	}
	clear_history_file();
	free_ms_data(data);
	free_signal_context();
}

void	handle_numeric_error(t_ms_data *data, const char *arg)
{
	char	*temp_str;

	temp_str = ft_strjoin("exit: ", arg);
	exit_status_handler(data, NUMERIC_REQUIRED, temp_str);
	free(temp_str);
	handle_exit(data, 0);
}

void	handle_too_many_args_error(t_ms_data *data)
{
	exit_status_handler(data, TOO_MANY_ARGS, "exit");
	handle_exit(data, TOO_MANY_ARGS);
}

void	handle_exit(t_ms_data *data, int status)
{
	if (status != 0 && status != TOO_MANY_ARGS)
		ft_putendl_fd("exit", STDOUT_FILENO);
	cleanup_exit_resources(data);
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
			ft_free_2d_arr(data->args);
			data->args = NULL;
			handle_exit(data, number);
		}
	}
	else
	{
		ft_free_2d_arr(data->args);
		data->args = NULL;
		ft_putendl_fd("exit", STDOUT_FILENO);
		handle_exit(data, 0);
	}
	return (EXIT_SUCCESS);
}
