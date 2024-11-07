/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmikhayl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 13:23:26 by rmikhayl          #+#    #+#             */
/*   Updated: 2024/09/09 13:27:44 by dmdemirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include "execute.h"
#include "shell.h"
#include "pipe.h"
#include "signals.h"
#include "exit_status.h"
#include "builtins.h"

int	status_handler(int status, \
				t_loop_data *loop_data, t_token *token_head);
void	process_ast_and_io(t_ms_data *data, \
				t_loop_data *loop_data, t_token *tokens_head);
void	main_loop(t_ms_data *data, t_loop_data *loop_data);
int			main(int argc, char **argv, char **envp);

int	status_handler(int status, \
				t_loop_data *loop_data, t_token *tokens_head)
{
	if (status == EXIT_FAILURE)
	{
		loop_cleanup(loop_data, tokens_head);
		return (0);
	}
	return (1);
}

void	process_ast_and_io(t_ms_data *data, \
				t_loop_data *loop_data, t_token *tokens_head)
{
	int	status;

	status = execute_ast(loop_data->tree, data);
	printf("execute ast exit status -> %d\n", status);
	data->exit_status = status;
	set_shell_var_handler(data);
	if (status_handler(status, loop_data, tokens_head))
	{
		handle_io_fd(data);
		loop_cleanup(loop_data, tokens_head);
	}
}

void	main_loop(t_ms_data *data, t_loop_data *loop_data)
{
	t_token	*tokens_start;

	while (1)
	{
		set_signals_interactive(data);
		loop_data->input = readline("🌴 maxishell> ");
		set_signals_noninteractive();
		if (!loop_data->input || !ft_strncmp(loop_data->input, "exit", 4))
		{
			data->args = ft_split(loop_data->input, ' ');
			builtin_exit(data);
		}
		make_history(loop_data->input);
		loop_data->trimmed_input = trim_input(loop_data->input);
		if (input_error_checks(loop_data))
			continue ;
		loop_data->tokens = tokenise(loop_data->trimmed_input);
		tokens_start = loop_data->tokens;
		loop_data->tree = parse_tokens(&loop_data->tokens, data);
		print_ast_root(loop_data->tree);
		process_ast_and_io(data, loop_data, tokens_start);
	}
	clear_history_file();
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
	clear_history_file();
	return (0);
}
