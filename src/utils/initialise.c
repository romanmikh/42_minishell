/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmikhayl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 18:16:59 by rmikhayl          #+#    #+#             */
/*   Updated: 2024/06/06 18:17:39 by rmikhayl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include "env.h"

void	init_minishell_data(t_minishell_data *data, char **envp)
{
	data->args = NULL;
	data->envp = NULL;
	init_env(&data->envp, envp);
	data->local_env = NULL;
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
		printf("Usage: %s\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	read_history(HISTORY_PATH);
}
