/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmdemirk <dmdemirk@student.42london.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:05:18 by dmdemirk          #+#    #+#             */
/*   Updated: 2024/06/04 12:44:38 by dmdemirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include "execute.h"
#include "shell.h"

void	init_minishell_data(t_minishell_data *data, char **envp);

void	handle_args(t_token **tokens, char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		add_node(tokens, argv[i]);
		i++;
	}
}

// getpwuid(geteuid())->pw_name // username, but uses disallowed functions
int	main(int argc, char **argv, char **envp)
{
	char		*line;
	int			repeat;
	char		**parsed_text;
	const char	*history_file;
	t_token		*tokens;
	t_minishell_data	data;

	init_minishell_data(&data, envp);
	if (argc > 1)
	{
		printf("Usage: %s\n", argv[0]);
		return (1);
	}

	history_file = "./utils/.maxishell_history";
	read_history(history_file);
	repeat = 1;
	while (repeat)
	{
		tokens = NULL;
		line = readline("🌴\e[1m dimrom@maxishell-> \e[m");
		if (!line || ft_strcmp(line, "exit") == 0)
			break ;
		if (*line)
			add_history(line);
		write_history(history_file);
		parsed_text = ft_split(line, ' ');
		// printf("\033[31m@maxishell: command not found: %s\033[0m\n", parsed_text[0]);
		handle_args(&tokens, parsed_text);
		data.args = list_to_array(tokens);
		execute(&data);
		// print_stack(&tokens);
		free_stack(&tokens);
		free(line);
		free(data.args);
	}
	return (0);
}


void	init_minishell_data(t_minishell_data *data, char **envp)
{
	data->args = NULL;
	data->envp = envp;
	data->current_dir = getcwd(NULL, 0);
	data->exit_status = 0;
}
