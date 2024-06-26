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
#include "pipe.h"

// int	main_loop(t_minishell_data data)
// {
// 	t_ast				*tree;
// 	char				*input;
// 	t_token				*tokens;
// 	char				*prompt;
// 	char				*trimmed_input;
// 	int					status;

// 	// prompt = generate_prompt(&data);
// 	prompt = generate_prompt();
// 	input = readline(prompt);
// 	if (!input)
// 		return (1);
// 	make_history(input);
// 	trimmed_input = trim_input(input);
// 	input_error_checks(trimmed_input);
// 	tokens = tokenise(trimmed_input);
// 	if (tokens)
// 	{
// 		tree = parse_tokens(&tokens);
// 		// print_ast_root(tree);
// 		status = execute_ast(tree, &data);
// 		if (status == WAIT_NEXT_COMMAND)
// 			continue ;
// 		if(data.temp_fd != -1)
// 			close(data.temp_fd);
// 		loop_cleanup(trimmed_input, tokens, prompt, tree);
// 		return (0);
// 	}
// 	return (1);
// }

int main(int argc, char **argv, char **envp)
{
    t_minishell_data    data;
    t_ast               *tree;
    char                *input;
    t_token             *tokens;
    char                *prompt;
    char                *trimmed_input;
    int                 status;

    print_maxishell();
    init_minishell_data(&data, envp);
    initialise(argc, argv);
    while (1)
    {
        prompt = generate_prompt(&data);
        input = readline(prompt);
        make_history(input);
        trimmed_input = trim_input(input);
        // input_error_checks(trimmed_input);
        tokens = tokenise(trimmed_input);
        tree = parse_tokens(&tokens);
        status = execute_ast(tree, &data);
        if (status == WAIT_NEXT_COMMAND)
        {
            loop_cleanup(trimmed_input, tokens, prompt, tree);
			printf("WAIT_NEXT_COMMAND\n");
            continue ;
        }
        if (data.temp_fd != -1)
        {
            close(data.temp_fd);
            data.temp_fd = -1;
        }
        loop_cleanup(trimmed_input, tokens, prompt, tree);
    }
    free_minishell_data(&data);
    free_env(data.envp);
    return 0;
}
