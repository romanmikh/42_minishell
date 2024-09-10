/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmikhayl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 18:16:59 by rmikhayl          #+#    #+#             */
/*   Updated: 2024/09/06 12:00:14 by dmdemirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include "env.h"
#include "signals.h"

void	init_ms_data(t_ms_data *data, char **argv, char **envp);
void	initialise(int argc, char **argv);

void	init_ms_data(t_ms_data *data, char **argv, char **envp)
{
	(void)argv;
	data->args = NULL;
	data->envp = NULL;
	init_env(&data->envp, envp);
	data->shell_variables = NULL;
	handle_add_set_shell_variable(&data->shell_variables, "_=/usr/bin/env");
	set_shell_var(&data->shell_variables, "?", "0");
	data->current_dir = getcwd(NULL, 0);
	data->exit_status = 0;
	data->std_in = -1;
	data->std_out = -1;
	data->std_err = 2;
}

void	initialise(int argc, char **argv)
{
	if (argc > 1)
	{
		ft_printf("Usage: %s\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	read_history(HISTORY_PATH);
}
