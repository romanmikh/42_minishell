/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmikhayl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:16:03 by rmikhayl          #+#    #+#             */
/*   Updated: 2024/06/05 14:18:08 by rmikhayl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"

//void	handle_quotes(char **tokens, int *pos, char **input)
//{
//	char	quote;
//	char	*start;
//
//	quote = *(*input)++;
//	start = *input;
//	while (**input && **input != quote)
//		(*input)++;
//	if (**input == '\0')
//	{
//		printf("@maxishell: syntax error: unmatched %c\n", quote);
//		free(tokens);
//		tokens = NULL;
//		return ;
//	}
//	**input = '\0';
//	tokens[*pos] = ft_strdup(start);
//	(*input)++;
//	if (strlen(tokens[*pos]) > 0)
//		(*pos)++;
//}
//
//void	handle_special_chars(char **tokens, int *pos, char **input)
//{
//	if ((**input == '<' && *(*input + 1) == '<') || (**input == '>' && *(*input + 1) == '>'))
//	{
//		tokens[*pos] = strndup(*input, 2);
//		(*input) += 2;
//	}
//	else
//	{
//		tokens[*pos] = strndup(*input, 1);
//		(*input)++;
//	}
//	(*pos)++;
//}
//
//void	handle_regular_chars(char **tokens, int *pos, char **input, char *delim)
//{
//	char	*start;
//
//	start = *input;
//	while (**input && !strchr(delim, **input) && **input != '|' && **input != '<' && **input != '>' && **input != '\"' && **input != '\'')
//		(*input)++;
//	tokens[*pos] = strndup(start, *input - start);
//	(*pos)++;
//}
//
//void	skip_delimiters(char **input, char *delim)
//{
//	while (**input && strchr(delim, **input))
//		(*input)++;
//}
