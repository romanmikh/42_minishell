/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmikhayl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 13:23:26 by rmikhayl          #+#    #+#             */
/*   Updated: 2024/06/05 17:18:03 by rmikhayl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include "execute.h"
#include "shell.h"

void	init_minishell_data(t_minishell_data *data, char **envp)
{
	data->args = NULL;
	data->envp = envp;
	data->current_dir = getcwd(NULL, 0);
	data->exit_status = 0;
}

void	execute_command(char **parsed_text, t_token **tokens)
{
	if (parsed_text != NULL)
	{
		printf("\033[31m@maxishell: command not found: \
				%s\033[0m\n", parsed_text[0]);
		build_linked_list(tokens, parsed_text);
		print_stack(tokens);
	}
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

int	main(int argc, char **argv, char **envp)
{
	t_minishell_data	data;
	char				*line;
	t_token				*tokens;
	char				**parsed_text;

	init_minishell_data(&data, envp);
	initialise(argc, argv);
	while (1)
	{
		tokens = NULL;
		line = readline(generate_prompt());
		if (!line || ft_strcmp(line, "exit") == 0)
			break ;
		make_history(line);
		parsed_text = parse_input(line);
		execute_command(parsed_text, &tokens);
		data.args = list_to_array(tokens);
		execute(&data);
		cleanup(line, parsed_text, tokens);
	}
	return (0);
}
