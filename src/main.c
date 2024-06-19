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

const char *get_token_type_name(t_token_type type)
{
    switch (type)
    {
    case PHRASE:
        return "PHRASE";
    case PIPE:
        return "PIPE";
    case ENV_VAR:
        return "ENV_VAR";
    case REDIR_IN:
        return "REDIR_IN";
    case REDIR_OUT:
        return "REDIR_OUT";
    case REDIR_APPEND:
        return "REDIR_APPEND";
    case REDIR_HEREDOC:
        return "REDIR_HEREDOC";
    default:
        return "UNKNOWN";
    }
}
void print_ast_graphical(t_ast *node, int depth, char *prefix, int is_left)
{
    if (!node)
        return;

    printf("%s", prefix);

    if (depth == 0)
        printf("Root-> ");
    else
        printf("%s-> ", is_left ? "L" : "R");

    printf("Type: %s\n", get_token_type_name(node->type));

    if (node->args)
    {
        for (int i = 0; node->args[i]; i++)
        {
            printf("%s     Arg: %s\n", prefix, node->args[i]);
        }
    }

    char new_prefix[256];
    snprintf(new_prefix, sizeof(new_prefix), "%s%s", prefix, is_left ? "|  " : "   ");

    if (node->left)
    {
        print_ast_graphical(node->left, depth + 1, new_prefix, 1);
    }

    if (node->right)
    {
        print_ast_graphical(node->right, depth + 1, new_prefix, 0);
    }
}

void print_ast_root(t_ast *root)
{
    print_ast_graphical(root, 0, "", 0);
}
int	main_loop(t_minishell_data data)
{
	t_ast				*tree;
	char				*input;
	t_token				*tokens;
	char				*prompt;
	char				*trimmed_input;

	prompt = generate_prompt(&data);
	input = readline(prompt);
	if (!input)
		return (1);
	make_history(input);
	trimmed_input = trim_input(input);
	input_error_checks(trimmed_input);
	tokens = tokenise(trimmed_input);
	if (tokens)
	{
		print_tokens(tokens);
		ft_printf("^tokens before entering the tree\n");
		tree = parse_tokens(&tokens);
		printf(GRN "Hell yeah we're out of the tree\n" RESET);
		print_ast_root(tree);
		execute_ast(tree, &data);
		loop_cleanup(trimmed_input, tokens, prompt, tree);
		return (0);
	}
	return (1);
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
