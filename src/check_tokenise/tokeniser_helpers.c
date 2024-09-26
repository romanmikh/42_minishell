/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokeniser_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rocky <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 10:38:28 by rocky             #+#    #+#             */
/*   Updated: 2024/09/09 15:47:48 by dmdemirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"

void	print_tokens(t_token *tokens, char *name);
void	print_ast_args(t_ast *node);
void	append_word_if_valid(char *start, char *str, t_token **tokens);

void	print_tokens(t_token *tokens, char *name)
{
	t_token	*token;
	int		i;				

	i = 0;
	token = tokens;
	if (ft_strlen(name) > 0)
		ft_printf(GRN"----- 		%s[]		-----\n"RESET, name);
	while (token != NULL)
	{
		ft_printf(GRN"input[%d] ->  	%s		at add:			%p\n"RESET, \
			i, token->data, &token->data);
		token = token->next;
		i++;
	}
}

void	print_ast_args(t_ast *node)
{
	int		i;				

	i = 0;
	while (node->args[i] != NULL)
	{
		ft_printf("ast arg[%d] ->  %s \n", i, node->args[i]);
		i++;
	}
}

void	append_word_if_valid(char *start, char *str, t_token **tokens)
{
	char	*word;

	if (str > start)
	{
		word = ft_strndup(start, str - start);
		if (word)
		{
			append_token(tokens, new_token(word, PHRASE));
			free(word);
		}
		else
			ft_printf("Error: unable to allocate memory for token\n");
	}
}
