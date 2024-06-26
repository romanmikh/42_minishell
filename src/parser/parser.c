/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rocky <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 19:35:45 by rocky             #+#    #+#             */
/*   Updated: 2024/06/26 15:00:24 by dmdemirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"

/*
	REFACTORING
*/

t_ast	*clr_node(t_token **tokens, t_token *next_token, t_ast *redirect_node);
t_ast	*manage_redirs(t_token **tokens);
t_ast	*create_redir_node(t_token *token);

t_ast	*create_redir_node(t_token *token)
{
	t_ast			*node;

	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type = token->type;
	node->args = malloc(sizeof(char *) * 2);
	if (!node->args)
	{
		free(node);
		return (NULL);
	}
	node->args[0] = token->data;
	node->args[1] = NULL;
	node->left = NULL;
	node->right = NULL;
	free(token);
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

t_ast	*clr_node(t_token **tokens, t_token *next_token, t_ast *redirect_node)
{
	(*tokens)->next = next_token->next->next;
	redirect_node->left = manage_redirs(tokens);
	redirect_node->right = create_redir_node((next_token->next));
	free(next_token->data);
	free(next_token);
	return (redirect_node);
}

t_ast	*manage_redirs(t_token **tokens)
{
	t_token		*tmp;
	t_ast		*redirect_node;
	t_token		*next_token;

	if (!*tokens)
		return (NULL);
	tmp = *tokens;
	if (is_redir_node(*tokens))
		return (create_redir(tokens, tmp));
	while (*tokens && (*tokens)->next)
	{
		next_token = (*tokens)->next;
		if (is_redir_node((*tokens)->next))
		{
			redirect_node = new_ast_node((*tokens)->next->type);
			return (clr_node(tokens, next_token, redirect_node));
		}
		*tokens = next_token;
	}
	return (manage_commands(&tmp));
}

t_ast	*manage_pipe(t_token **tokens)
{
	t_token		*tmp;
	t_token		*next_token;
	t_ast		*pipe_node;

	tmp = *tokens;
	while (*tokens && (*tokens)->next)
	{
		next_token = (*tokens)->next;
		if ((*tokens)->next->type == PIPE)
		{
			pipe_node = new_ast_node((*tokens)->next->type);
			(*tokens)->next = NULL;
			pipe_node->left = manage_redirs(&tmp);
			if (next_token->next == NULL)
			{
				pipe_node->right = NULL;
				pipe_node->incomplete = true;
			}
			else
			{
				pipe_node->right = manage_pipe(&(next_token->next));
				pipe_node->incomplete = false;
			}
			free(next_token->data);
			free(next_token);
			return (pipe_node);
		}
		*tokens = next_token;
	}
	return (manage_redirs(&tmp));
}

t_ast	*parse_tokens(t_token **tokens)
{
	if (!tokens || !*tokens)
		return (NULL);
	return (manage_pipe(tokens));
}

//void print_spaces(int count) {
//    for (int i = 0; i < count; i++) {
//        printf("  ");
//    }
//}
//
//void print_ast_node(t_ast *node, int depth) {
//    if (node == NULL) {
//        return;
//    }
//    print_spaces(depth);
//    switch (node->type) {
//        case PHRASE:
//            printf("COMMAND: ");
//            for (int i = 0; node->args && node->args[i]; i++) {
//                printf("%s ", node->args[i]);
//            }
//            printf("\n");
//            break;
//        case REDIR_IN:
//            printf("REDIRECTION IN: %s\n", node->args[0]);
//            break;
//        case REDIR_OUT:
//            printf("REDIRECTION OUT: %s\n", node->args[0]);
//            break;
//        case REDIR_APPEND:
//            printf("REDIRECTION APPEND: %s\n", node->args[0]);
//            break;
//        case REDIR_HEREDOC:
//            printf("REDIRECTION HEREDOC: %s\n", node->args[0]);
//            break;
//        case PIPE:
//            printf("PIPE\n");
//            break;
//        default:
//            printf("UNKNOWN NODE TYPE\n");
//            break;
//    }
//    if (node->left) {
//        print_ast_node(node->left, depth + 1);
//    }
//    if (node->right) {
//        print_ast_node(node->right, depth + 1);
//    }
//}
//void visualize_ast(t_ast *root) {
//   print_ast_node(root, 0);
//}
