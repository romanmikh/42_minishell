/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AST.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rocky <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 19:35:45 by rocky             #+#    #+#             */
/*   Updated: 2024/09/09 16:18:58 by dmdemirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"

t_ast	*manage_redirs(t_token **tokens, t_ms_data *data);
t_ast	*create_redir_node(t_token *token);
int		is_redir_node(t_token *tokens);
t_ast	*new_ast_node(void);

t_ast	*manage_redirs(t_token **tokens, t_ms_data *data)
{
	t_ast		*command_node;
	t_ast		*redirect_node;
	t_token		*current_token;

	if (!tokens || !*tokens)
		return (NULL);
	command_node = manage_commands(tokens, data);
	current_token = *tokens;
	while (current_token && is_redir_node(current_token))
	{
		redirect_node = create_redir_node(current_token);
		redirect_node->left = command_node;
		*tokens = current_token->next;
		if (*tokens)
		{
			redirect_node->right = create_redir_node(*tokens);
			*tokens = (*tokens)->next;
		}
		else
			redirect_node->right = NULL;
		command_node = redirect_node;
		current_token = *tokens;
	}
	return (command_node);
}

void	set_command_args(t_ast *command_node, t_token **tokens, int arg_count)
{
	int	i;

	i = 0;
	while (i < arg_count)
	{
		command_node->args[i] = ft_strdup((*tokens)->data);
		*tokens = (*tokens)->next;
		i++;
	}
	command_node->args[arg_count] = NULL;
}

t_ast	*create_redir_node(t_token *token)
{
	t_ast			*node;

	node = new_ast_node();
	node->type = token->type;
	node->args = malloc(sizeof(char *) * 2);
	if (!node->args)
	{
		free(node);
		return (NULL);
	}
	node->args[0] = ft_strdup(token->data);
	node->args[1] = NULL;
	return (node);
}

int	is_redir_node(t_token *tokens)
{
	if (tokens->type == REDIR_IN
		|| tokens->type == REDIR_OUT
		|| tokens->type == REDIR_APPEND
		|| tokens->type == REDIR_HEREDOC)
		return (1);
	return (0);
}

t_ast	*new_ast_node(void)
{
	t_ast		*node;

	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type = NONE;
	node->args = NULL;
	node->left = NULL;
	node->right = NULL;
	return (node);
}
