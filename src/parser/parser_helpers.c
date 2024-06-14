/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rocky <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 10:45:48 by rocky             #+#    #+#             */
/*   Updated: 2024/06/14 10:45:52 by rocky            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"

t_ast	*new_ast_node(t_token_type type)
{
	t_ast		*node;

	ft_printf(GRN "new_ast_node\n" RESET);
	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type = type;
	node->args = NULL;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

t_ast	*create_and_link_redirection(t_token **tokens, t_token *tmp)
{
	t_ast	*redirect_node;

	ft_printf(BLU "tokens inside create_and_link_redirection\n");
	print_tokens(*tokens);
	ft_printf("" RESET);
	redirect_node = new_ast_node((*tokens)->type);
	*tokens = (*tokens)->next->next;
	redirect_node->left = manage_redirections(tokens);
	redirect_node->right = create_redir_node(tmp->next);
	free(tmp->data);
	free(tmp);
	return (redirect_node);
}

int	arg_len(t_token *current)
{
	int	arg_count;

	arg_count = 0;
	while (current && current->type == PHRASE)
	{
		arg_count++;
		current = current->next;
	}
	ft_printf(GRN "counted %d args\n" RESET, arg_count);
	return (arg_count);
}

void	fill_command_arguments(t_ast *command_node, t_token **tokens, \
			int arg_count)
{
	int		i;
	t_token	*tmp;

	ft_printf(MAG "tokens inside fill_command_arguments\n");
	print_tokens(*tokens);
	ft_printf("" RESET);
	i = 0;
	while (i < arg_count)
	{
		command_node->args[i] = ft_strdup((*tokens)->data);
		tmp = *tokens;
		*tokens = (*tokens)->next;
		free(tmp->data);
		free(tmp);
		i++;
	}
	command_node->args[arg_count] = NULL;
}

t_ast	*manage_commands(t_token **tokens)
{
	t_ast		*command_node;
	int			arg_count;

	ft_printf(YEL "tokens inside fill_command_arguments\n");
	print_tokens(*tokens);
	ft_printf("" RESET);
	command_node = new_ast_node(PHRASE);
	arg_count = arg_len(*tokens);
	command_node->args = malloc(sizeof(char *) * (arg_count + 1));
	if (!command_node->args)
		return (NULL);
	fill_command_arguments(command_node, tokens, arg_count);
	return (command_node);
}
