/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AST_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmdemirk <dmdemirk@student.42london.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:56:45 by dmdemirk          #+#    #+#             */
/*   Updated: 2024/09/09 16:17:58 by dmdemirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include "shell.h"

t_ast	*parse_tokens(t_token **tokens, t_ms_data *data);
t_ast	*create_pipe_node(t_token *next_token, t_token **tokens, \
		t_ms_data *data, t_token *tmp);
t_ast	*manage_pipe(t_token **tokens, t_ms_data *data);
t_ast	*manage_commands(t_token **tokens, t_ms_data *data);
int		cmd_arg_len(t_token *current);

t_ast	*parse_tokens(t_token **tokens, t_ms_data *data)
{
	if (!tokens || !*tokens)
		return (NULL);
	return (manage_pipe(tokens, data));
}

t_ast	*create_pipe_node(t_token *next_token, t_token **tokens, \
		t_ms_data *data, t_token *tmp)
{
	t_ast	*pipe_node;

	pipe_node = new_ast_node();
	if (!pipe_node)
		return (NULL);
	pipe_node->type = next_token->type;
	pipe_node->args = malloc(sizeof(char *) * 2);
	if (!pipe_node->args)
	{
		free(pipe_node);
		return (NULL);
	}
	pipe_node->args[0] = ft_strdup(next_token->data);
	pipe_node->args[1] = NULL;
	pipe_node->left = manage_redirs(&tmp, data);
	*tokens = next_token->next;
	if (next_token->next)
		pipe_node->right = manage_pipe(tokens, data);
	else
		pipe_node->right = NULL;
	return (pipe_node);
}

t_ast	*manage_pipe(t_token **tokens, t_ms_data *data)
{
	t_token	*tmp;
	t_token	*next_token;

	tmp = *tokens;
	while (*tokens && (*tokens)->next)
	{
		next_token = (*tokens)->next;
		if (next_token->type == PIPE)
			return (create_pipe_node(next_token, tokens, data, tmp));
		*tokens = next_token;
	}
	return (manage_redirs(&tmp, data));
}

t_ast	*manage_commands(t_token **tokens, t_ms_data *data)
{
	t_ast		*command_node;
	int			cmd_arg_count;

	command_node = new_ast_node();
	command_node->type = PHRASE;
	cmd_arg_count = cmd_arg_len(*tokens);
	command_node->args = malloc(sizeof(char *) * (cmd_arg_count + 1));
	if (!command_node->args)
		return (NULL);
	set_command_args(command_node, tokens, cmd_arg_count);
	post_process_command_args(command_node, cmd_arg_count, data);
	return (command_node);
}

int	cmd_arg_len(t_token *current)
{
	int	i;

	i = 0;
	while (current && current->type == PHRASE)
	{
		i++;
		current = current->next;
	}
	return (i);
}
