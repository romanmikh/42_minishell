/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmikhayl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 13:23:26 by rmikhayl          #+#    #+#             */
/*   Updated: 2024/06/11 15:22:12 by rocky            ###   ########.fr       */
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

void	main_loop(t_minishell_data data)
{
	char				*prompt;
	char				*line;
	t_token				*tokens;
	char				**parsed_text;

	prompt = generate_prompt(&data);
	tokens = NULL;
	line = readline(prompt);

	is_exit_status_var(line);
	//line = check_heredoc(line);
	if (!line)
		exit(EXIT_FAILURE);
	make_history(line);
	input_error_checks(line);
	parsed_text = ft_split(line, ' ');
	execute_command(parsed_text, &tokens);
	data.args = list_to_array(tokens);
	execute(&data);
	cleanup(line, parsed_text, tokens, prompt);
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell_data	data;

	print_maxishell();
	init_minishell_data(&data, envp);
	initialise(argc, argv);
	while (1)
		main_loop(data);
	free_minishell_data(&data);
	free_env(data.envp);
	return (0);
}
