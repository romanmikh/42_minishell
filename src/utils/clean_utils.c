/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmdemirk <dmdemirk@student.42london.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:40:48 by dmdemirk          #+#    #+#             */
/*   Updated: 2024/09/09 15:41:11 by dmdemirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"

void	free_all_tokes(t_token *tokens);

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
