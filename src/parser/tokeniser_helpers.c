/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokeniser_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rocky <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 10:38:28 by rocky             #+#    #+#             */
/*   Updated: 2024/06/14 10:38:30 by rocky            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"

t_token	*new_token(char *value, t_token_type type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->data = ft_strdup(value);
	if (!token->data)
	{
		free(token);
		return (NULL);
	}
	token->type = type;
	token->next = NULL;
	return (token);
}

void	append_token(t_token **tokens, t_token *new_token)
{
	t_token	*prev;

	if (!*tokens)
		*tokens = new_token;
	else
	{
		prev = *tokens;
		while (prev->next)
			prev = prev->next;
		prev->next = new_token;
	}
}
