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

t_token *new_token(char *value, t_token_type type)
{
	t_token *token;

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
	t_token *prev;

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

void	free_all_tokens(t_token *tokens)
{
	t_token	*temp;

	while (tokens)
	{
		temp = tokens;
		tokens = tokens->next;
		free(temp->data);
		//free(temp->type);
		free(temp);
	}
}

void	handle_special_chars(char **str, t_token **tokens)
{
	ft_printf("%s <-- phrase st start of handle_special_chars\n", str);
	if (**str == '<')
	{
	printf("%s fu\n", *str);
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
	ft_printf("%s <-- append_phrase starting var\n", *str);

	if (*str > *start)
	{
		phrase = ft_strndup(*start, *str - *start);
		if (phrase)
		{
			ft_printf("%s <-- phrase appended\n", phrase);
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
	ft_printf("%s <-- phrase in handle_phrase\n", *str);
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

t_token *tokenise(char *str)
{
	t_token *tokens;
	ft_printf("%s <-- in tokenise()\n", str);
	
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
