/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmikhayl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 13:23:26 by rmikhayl          #+#    #+#             */
/*   Updated: 2024/06/07 19:01:19 by rmikhayl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include "execute.h"
#include "shell.h"

void	exit_status_var(void)
{
	ft_printf("\033[0;93mTODO: add logic for '$?'\n");
}

void	is_exit_status_var(char *line)
{
	char	*var_pos;

	var_pos = ft_strstr(line, "$?");
	if (var_pos != 0)
		exit_status_var();
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell_data	data;
	char				*line;
	t_token				*tokens;
	char				**parsed_text;

	print_maxishell();
	init_minishell_data(&data, envp);
	initialise(argc, argv);
	while (1)
	{
		tokens = NULL;
		line = readline(generate_prompt(&data));
		is_exit_status_var(line);
		line = check_heredoc(line);
		if (!line || ft_strcmp(line, "exit") == 0)
			break ;
		make_history(line);
		parsed_text = parse_input(line);
		execute_command(parsed_text, &tokens);
		data.args = list_to_array(tokens);
		// int i = -1;
		// while (data/.args[++i])
			// printf("args[%d]: %s\n", i, data.args[i]);
		execute(&data);
		cleanup(line, parsed_text, tokens);
	}
	return (0);
}
