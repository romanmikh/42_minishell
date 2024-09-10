/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmdemirk <dmdemirk@student.42london.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 11:34:39 by dmdemirk          #+#    #+#             */
/*   Updated: 2024/09/06 11:48:50 by dmdemirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exit_status.h"
#include "libft.h"
#include <unistd.h>
#include "shell.h"

#include <stdio.h>

void	exit_status_handler(t_ms_data *data, int status_code, char *err_arg);
void	ft_puterror(char *err_arg, char *error_message);
void	set_exit_status(int *exit_status, int status_code);
void	set_shell_var_handler(t_ms_data *data);

void	exit_status_handler(t_ms_data *data, int status_code, char *err_arg)
{
	char	*error_message;

	error_message = NULL;
	if (status_code == IS_DIRECTORY)
		error_message = "No such file or directory";
	else if (status_code == NUMERIC_REQUIRED)
		error_message = "numeric argument required";
	else if (status_code == TOO_MANY_ARGS)
		error_message = "too many arguments";
	else if (status_code == UNKNOWN_COMMAND)
		error_message = "command not found";
	else if (status_code == INVALID_ARGUMENT)
		error_message = "invalid argument";
	else if (status_code == PERMISSION_DENIED)
		error_message = "permission denied";
	else if (status_code == NOT_VALID_IDENTIFIER)
		error_message = "unset: not a valid identifier";
	else if (status_code == INVALID_OPTION)
		error_message = "invalid option";
	else
		error_message = "error";
	ft_puterror(err_arg, error_message);
	set_exit_status(&data->exit_status, status_code);
	set_shell_var_handler(data);
}

void	set_shell_var_handler(t_ms_data *data)
{
	char	*tmp_var;

	tmp_var = ft_itoa(data->exit_status);
	set_shell_var(&data->shell_variables, "?", tmp_var);
	free(tmp_var);
}

void	ft_puterror(char *err_arg, char *error_message)
{
	if (err_arg)
	{
		ft_putstr_fd("bash: ", STDERR_FILENO);
		ft_putstr_fd(err_arg, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putendl_fd(error_message, STDERR_FILENO);
	}
	else
	{
		ft_putstr_fd("bash: ", STDERR_FILENO);
		ft_putendl_fd(error_message, STDERR_FILENO);
	}
}

void	set_exit_status(int *exit_status, int status_code)
{
	*exit_status = status_code;
}
