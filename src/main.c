/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmikhayl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 13:23:26 by rmikhayl          #+#    #+#             */
/*   Updated: 2024/06/05 14:36:59 by rmikhayl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"

void	execute_command(char **parsed_text, t_token **tokens)
{
	char	**arr;

	if (parsed_text != NULL)
	{
		printf("\033[31m@maxishell: command not found: \
				%s\033[0m\n", parsed_text[0]);
		build_linked_list(tokens, parsed_text);
		arr = list_to_array(*tokens);
		print_stack(tokens);
		free_stack(tokens);
		free(arr);
	}
}

void	cleanup(char *line, char **parsed_text)
{
	free(line);
	free(parsed_text);
}

int	main(void)
{
	char		*line;
	int			repeat;
	char		**parsed_text;
	t_token		*tokens;
	const char	*history_file;

	history_file = "./utils/.maxishell_history";
	read_history(history_file);
	repeat = 1;
	while (repeat)
	{
		tokens = NULL;
		line = readline(generate_prompt());
		if (!line || ft_strcmp(line, "exit") == 0)
			break ;
		if (*line)
			add_history(line);
		write_history(history_file);
		parsed_text = parse_input(line);
		execute_command(parsed_text, &tokens);
		cleanup(line, parsed_text);
	}
	return (0);
}
