/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rocky <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 19:35:45 by rocky             #+#    #+#             */
/*   Updated: 2024/06/12 19:35:48 by rocky            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"

t_ast	*manage_redirections(t_token **tokens);
t_ast	*create_redir_node(t_token *token);


t_ast	*new_ast_node(t_token_type type)
{
	t_ast		*node;

	ft_printf("new_ast_node\n");
	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type = type;
	node->args = NULL;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

void	free_ast(t_ast *node)
{
	int				i;

	i = 0;
	if (!node)
		return ;
	if (node->type == PHRASE && node->args)
	{
		while (node->args && node->args[i])
		{
			free(node->args[i]);
			i++;
		}
		free(node->args);
	}
	free_ast(node->left);
	free_ast(node->right);
	free(node);
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
	ft_printf("counted %d args\n", arg_count);
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

t_ast	*create_redir_node(t_token *token)
{
	t_ast			*node;

	ft_printf("create_redir_node\n");
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

t_ast	*manage_redirections(t_token **tokens)
{
	t_token		*tmp;
	t_ast		*redirect_node;
	t_token		*next_token;

	ft_printf(GRN"tokens inside manage_redirections\n");
	print_tokens(*tokens);
	ft_printf("" RESET);
	if (!*tokens)
		return (NULL);
	tmp = *tokens;
	if ((*tokens)->type >= REDIR_IN
		&& (*tokens)->type <= REDIR_HEREDOC)
		return (create_and_link_redirection(tokens, tmp));
	while (*tokens && (*tokens)->next)
	{
		next_token = (*tokens)->next;
		if ((*tokens)->next->type >= REDIR_IN
			&& (*tokens)->next->type <= REDIR_HEREDOC)
		{
			redirect_node = new_ast_node((*tokens)->next->type);
			(*tokens)->next = next_token->next->next;
			redirect_node->left = manage_redirections(&tmp);
			redirect_node->right = create_redir_node((next_token->next));
			return (free(next_token->data), free(next_token), redirect_node);
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

	ft_printf(RED "tokens inside manage_pipe\n");
	print_tokens(*tokens);
	ft_printf("" RESET);
	tmp = *tokens;
	while (*tokens && (*tokens)->next)
	{
		next_token = (*tokens)->next;
		if ((*tokens)->next->type == PIPE)
		{
			pipe_node = new_ast_node((*tokens)->next->type);
			(*tokens)->next = NULL;
			pipe_node->left = manage_redirections(&tmp);
			pipe_node->right = manage_pipe(&(next_token->next));
			free(next_token->data);
			free(next_token);
			return (pipe_node);
		}
		*tokens = next_token;
	}
	return (manage_redirections(&tmp));
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
