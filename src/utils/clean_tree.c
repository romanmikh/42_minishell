/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rocky <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 13:21:30 by rocky             #+#    #+#             */
/*   Updated: 2024/06/14 13:21:49 by rocky            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"

// unused since tree freed on the fly
void	free_all_tokens(t_token *tokens)
{
	t_token	*temp;

	while (tokens)
	{
		temp = tokens;
		tokens = tokens->next;
		if (temp)
		{
			if (temp->data)
			{
				free(temp->data);
				temp->data = NULL;
			}
		}
		free(temp);
		temp = NULL;
	}
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
