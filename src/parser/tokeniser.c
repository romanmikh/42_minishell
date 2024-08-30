/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokeniser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rocky <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:00:23 by rocky             #+#    #+#             */
/*   Updated: 2024/06/12 15:00:25 by rocky            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include <string.h>

void	handle_special_chars(char **str, t_token **tokens)
{
	if (**str == '<')
	{
		if (*(*str + 1) == '<')
		{
			append_token(tokens, new_token("<<", REDIR_HEREDOC));
			(*str)++;
		}
		else
			append_token(tokens, new_token("<", REDIR_IN));
	}
	else if (**str == '>')
	{
		if (*(*str + 1) == '>')
		{
			append_token(tokens, new_token(">>", REDIR_APPEND));
			(*str)++;
		}
		else
			append_token(tokens, new_token(">", REDIR_OUT));
	}
	else if (**str == '|')
		append_token(tokens, new_token("|", PIPE));
	(*str)++;
}

void	append_phrase_if_valid(char **start, char **str, t_token **tokens)
{
	char	*phrase;

	if (*str > *start)
	{
		phrase = ft_strndup(*start, *str - *start);
		if (phrase)
		{
			append_token(tokens, new_token(phrase, PHRASE));
			free(phrase);
		}
		else
			ft_printf("Error: unable to allocate memory for token\n");
	}
}

void	handle_phrase(char **str, t_token **tokens)
{
	char	*start;
	char	quote_flag;
	char	quote_type;

	start = *str;
	quote_flag = 0;
	quote_type = 0;
	while (**str)
	{
		if (!quote_flag && (**str == '\'' || **str == '\"'))
		{
			quote_flag = 1;
			quote_type = **str;
		}
		else if (quote_flag && **str == quote_type)
			quote_flag = 0;
		if (!quote_flag && ft_strchr(" \t\n\r\v\f<|>", **str) != NULL)
			break ;
		(*str)++;
	}
	append_phrase_if_valid(&start, str, tokens);
}

void	print_tokens(t_token *tokens)
{
	t_token	*token;
	int		i;				

	i = 0;
	token = tokens;
	while (token != NULL)
	{
		ft_printf("input[%d] ->  %s \n", i, token->data);
		token = token->next;
		i++;
	}
}

t_token	*tokenise(char *str)
{
	t_token	*tokens;

	tokens = NULL;
	while (*str)
	{
		while (*str && ft_strchr(" \t\n\r\v\f", *str) != NULL)
			str++;
		if (ft_strchr("<|>", *str) != NULL)
			handle_special_chars(&str, &tokens);
		else
			handle_phrase(&str, &tokens);
	}
	return (tokens);
}
