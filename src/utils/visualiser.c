/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualiser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmikhayl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 19:00:03 by rmikhayl          #+#    #+#             */
/*   Updated: 2024/06/07 19:16:18 by rmikhayl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"

const char	*get_token_type_name(t_token_type type)
{
	if (type == PHRASE)
		return ("PHRASE");
	else if (type == PIPE)
		return ("PIPE");
	else if (type == ENV_VAR)
		return ("ENV_VAR");
	else if (type == REDIR_IN)
		return ("REDIR_IN");
	else if (type == REDIR_OUT)
		return ("REDIR_OUT");
	else if (type == REDIR_APPEND)
		return ("REDIR_APPEND");
	else if (type == REDIR_HEREDOC)
		return ("REDIR_HEREDOC");
	else
		return ("UNKNOWN");
}

void	print_ast_node(t_ast *node, int depth, char *prefix, int is_left)
{
	int	i;

	if (!node)
		return ;
	ft_printf("%s", prefix);
	if (depth == 0)
		ft_printf("Root-> ");
	else
	{
		if (is_left)
			ft_printf("L-> ");
		else
			ft_printf("R-> ");
	}
	ft_printf("Type: %s\n", get_token_type_name(node->type));
	if (node->args)
	{
		i = 0;
		while (node->args[i])
		{
			ft_printf("%s     Arg: %s\n", prefix, node->args[i]);
			i++;
		}
	}
}

void	build_new_prefix(char *new_prefix, char *prefix, int is_left)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (prefix[i])
	{
		new_prefix[j] = prefix[i];
		i++;
		j++;
	}
	if (is_left)
	{
		new_prefix[j++] = '|';
		new_prefix[j++] = ' ';
		new_prefix[j++] = ' ';
	}
	else
	{
		new_prefix[j++] = ' ';
		new_prefix[j++] = ' ';
		new_prefix[j++] = ' ';
	}
	new_prefix[j] = '\0';
}

void	print_ast_graphical(t_ast *node, int depth, char *prefix, int is_left)
{
	char	new_prefix[256];

	print_ast_node(node, depth, prefix, is_left);
	build_new_prefix(new_prefix, prefix, is_left);
	if (node->left)
		print_ast_graphical(node->left, depth + 1, new_prefix, 1);
	if (node->right)
		print_ast_graphical(node->right, depth + 1, new_prefix, 0);
}

void	print_ast_root(t_ast *root)
{
	if (!root)
		return ;
	print_ast_graphical(root, 0, "", 0);
}
