/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmikhayl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:19:49 by rmikhayl          #+#    #+#             */
/*   Updated: 2024/06/11 15:30:44 by rocky            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"

void	allocate_tokens(char ***tokens, int bufsize)
{
	*tokens = malloc(bufsize * sizeof(char *));
	if (!*tokens)
	{
		printf("@maxishell: allocation error\n");
		exit(EXIT_FAILURE);
	}
}

void	reallocate_tokens(char ***tokens, int *bufsize)
{
	*bufsize += 64;
	*tokens = realloc(*tokens, *bufsize * sizeof(char *));
	if (!*tokens)
	{
		printf("@maxishell: allocation error\n");
		exit(EXIT_FAILURE);
	}
}

void	parse_loop(char **input, char **tokens, int *pos, int *bufsize)
{
	char	*delim;

	delim = " ";
	while (**input)
	{
		skip_delimiters(input, delim);
		if (**input == '\0')
			break ;
		if (**input == '\'' || **input == '\"')
			handle_quotes(tokens, pos, input);
		else if (**input == '|' || **input == '<' || **input == '>')
			handle_special_chars(tokens, pos, input);
		else
			handle_regular_chars(tokens, pos, input, delim);
		if (*tokens == NULL)
			return ;
		if (*pos >= *bufsize)
			reallocate_tokens(&tokens, bufsize);
	}
}

char	**parse_input(char *input)
{
	int		pos;
	int		bufsize;
	char	**tokens;

	pos = 0;
	bufsize = 64;
	allocate_tokens(&tokens, bufsize);
	parse_loop(&input, tokens, &pos, &bufsize);
	tokens[pos] = NULL;
	return (tokens);
}

void	execute_command(char **parsed_text, t_token **tokens)
{
	if (parsed_text != NULL)
	{
		build_linked_list(tokens, parsed_text);
		print_stack(tokens);
		ft_printf("---\n");
	}
}
