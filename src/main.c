/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmdemirk <dmdemirk@student.42london.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:05:18 by dmdemirk          #+#    #+#             */
/*   Updated: 2024/05/31 21:09:12 by rmikhayl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include "execute.h"

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
int	main(void)
{
	char		*line;
	int			repeat;
	char		**arr;
	char		**parsed_text;
	const char	*history_file;
	t_token		*tokens;

	history_file = "./utils/.maxishell_history";
	read_history(history_file);
	repeat = 1;
	while (repeat)
	{
		tokens = NULL;
		line = readline("🌴\e[1m dimrom@maxishell> \e[m");
		if (!line || ft_strcmp(line, "exit") == 0)
			break ;
		if (*line)
			add_history(line);
		write_history(history_file);
		parsed_text = ft_split(line, ' ');
		// printf("\033[31m@maxishell: command not found: %s\033[0m\n", parsed_text[0]);
		handle_args(&tokens, parsed_text);
		arr = list_to_array(tokens);
		execute(arr);
		print_stack(&tokens);
		free_stack(&tokens);
		free(line);
		free(arr);
	}
	return (0);
}
