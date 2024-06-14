/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rocky <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:51:08 by rocky             #+#    #+#             */
/*   Updated: 2024/06/11 16:53:40 by rocky            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"

int	check_operators(const char *str)
{
	int	single_quotes;
	int	double_quotes;
	int	cmd_flag;

	single_quotes = 0;
	double_quotes = 0;
	cmd_flag = 0;
	if (*str == '&' || *str == '|')
		return (1);
	while (*str)
	{
		if (*str == '\'')
			single_quotes++;
		if (*str == '\"')
			double_quotes++;
		if (*str == '|' && !(single_quotes % 2) && !(double_quotes % 2))
		{
			if (cmd_flag)
				return (1);
			cmd_flag = 1;
		}
		else if (ft_strchr(" \t\n\r\v\f", *str) != NULL)
			cmd_flag = 0;
		str++;
	}
	if (cmd_flag)
		return (1);
	return (0);
}

const char	*exclude_delimiters(const char *str)
{
	while (*str && (ft_strchr(" \t\n\r\v\f", *str) != NULL))
		str++;
	return (str);
}

int	valid_operator(const char **str)
{
	const char	*start;

	start = (*str)++;
	if (*start == **str)
		(*str)++;
	*str = exclude_delimiters(*str);
	if (**str == '<' || **str == '>' || **str == '|' || **str == '\0')
		return (0);
	return (1);
}

int	check_redirections(const char *str)
{
	int	single_quotes;
	int	double_quotes;

	single_quotes = 0;
	double_quotes = 0;
	while (*str)
	{
		if (*str == '\'')
			single_quotes++;
		if (*str == '\"')
			double_quotes++;
		if ((!(single_quotes % 2) && !(double_quotes % 2))
			&& (*str == '>' || *str == '<'))
		{
			if (!valid_operator(&str))
				return (1);
		}
		else
			str++;
	}
	return (0);
}

int	check_open_quotes(const char *str)
{
	int	single_quote_open;
	int	double_quote_open;

	single_quote_open = 0;
	double_quote_open = 0;
	while (*str)
	{
		if (*str == '\'' && !double_quote_open)
		{
			single_quote_open = !single_quote_open;
		}
		else if (*str == '"' && !single_quote_open)
			double_quote_open = !double_quote_open;
		str++;
	}
	return (single_quote_open || double_quote_open);
}

int	input_error_checks(const char *str)
{
	if (check_redirections(str))
		ft_printf("Input error: invalid redirection.\n");
	else if (check_operators(str))
		ft_printf("Input error: invalid operator.\n");
	else if (check_open_quotes(str))
		ft_printf("Input error: open quote.\n");
	else
	{
		//free(str);
		return (0);
	}
	//free(str);
	return (1);
}
