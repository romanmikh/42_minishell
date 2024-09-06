/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmikhayl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 13:23:26 by rmikhayl          #+#    #+#             */
/*   Updated: 2024/07/18 16:02:15 by dmdemirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include "execute.h"
#include "shell.h"
#include "pipe.h"
#include "signals.h"

int	status_handler(int status, t_loop_data *loop_data)
{
	if (status == WAIT_NEXT_COMMAND)
	{
		loop_cleanup(loop_data->trimmed_input, loop_data->tokens, \
				loop_data->prompt, loop_data->tree);
		return (0);
	}
	return (1);
}

void	process_ast_and_io(t_ms_data *data, t_loop_data *loop_data)
{
	int	status;

	print_ast_root(loop_data->tree);
	status = execute_ast(loop_data->tree, data);
	shell_variable_update(data, status);
	if (status_handler(status, loop_data))
	{
		handle_io_fd(data);
		loop_cleanup(loop_data->trimmed_input, loop_data->tokens, \
				loop_data->prompt, loop_data->tree);
	}
}

void	main_loop(t_ms_data *data, t_loop_data *loop_data)
{
	while (1)
	{
		loop_data->prompt = generate_prompt(data);
		set_signals_interactive();
		loop_data->input = readline(loop_data->prompt);
		set_signals_noninteractive();
		if (loop_data->input == NULL)
		{
			write(STDOUT_FILENO, "exit\n", 5);
			break ;
		}
		make_history(loop_data->input);
		loop_data->trimmed_input = trim_input(loop_data->input);
		if (input_error_checks(loop_data->trimmed_input))
			continue ;
		loop_data->tokens = tokenise(loop_data->trimmed_input);
		loop_data->tree = parse_tokens(&loop_data->tokens, data);
		process_ast_and_io(data, loop_data);
	}
	free(loop_data->prompt);
}

int	main(int argc, char **argv, char **envp)
{
	t_ms_data		data;
	t_loop_data		loop_data;

	print_maxishell();
	init_ms_data(&data, argv, envp);
	initialise(argc, argv);
	main_loop(&data, &loop_data);
	free_ms_data(&data);
	return (0);
}
