/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rocky <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 20:13:42 by rocky             #+#    #+#             */
/*   Updated: 2024/08/28 20:14:33 by rocky            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"

t_ast	*new_ast_node(t_token_type type);
t_ast	*create_redir(t_token **tokens, t_token *tmp, t_ms_data *data);
int		arg_len(t_token *current);
void	set_command_args(t_ast *command_node, t_token **tokens, int arg_count);
t_ast	*manage_commands(t_token **tokens, t_ms_data *data);

t_ast	*new_ast_node(t_token_type type)
{
	t_ast		*node;

	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type = type;
	node->args = NULL;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

t_ast	*create_redir(t_token **tokens, t_token *tmp, t_ms_data *data)
{
	t_ast	*redirect_node;

	redirect_node = new_ast_node((*tokens)->type);
	*tokens = (*tokens)->next->next;
	redirect_node->left = manage_redirs(tokens, data);
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
	return (arg_count);
}

void	set_command_args(t_ast *command_node, t_token **tokens, \
			int arg_count)
{
	int		i;
	t_token	*tmp;

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

t_ast	*manage_commands(t_token **tokens, t_ms_data *data)
{
	t_ast		*command_node;
	int			arg_count;

	command_node = new_ast_node(PHRASE);
	arg_count = arg_len(*tokens);
	command_node->args = malloc(sizeof(char *) * (arg_count + 1));
	if (!command_node->args)
		return (NULL);
	set_command_args(command_node, tokens, arg_count);
	post_process_command_args(command_node, arg_count, data);
	return (command_node);
}
