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

void	free_op_strings(t_loop_data *data, char *tail, char *new)
{
	free(data->trimmed_input);
	free(new);
	free(tail);
}

int	check_operators(t_loop_data *loop_data)
{
	char	*input;
	char	*tail;
	char	*new_input;
	char	*final_input;

	input = loop_data->trimmed_input;
	if (*input == '&' || *input == '|')
		return (1);
	while (*input)
	{
		if (*input == '|' && *(input + 1) == '\0')
		{
			tail = readline("> ");
			if (tail == NULL)
				break ;
			new_input = ft_strcat_const(loop_data->trimmed_input, " ");
			final_input = ft_strcat_const(new_input, tail);
			free_op_strings(loop_data, tail, new_input);
			loop_data->trimmed_input = final_input;
			free(final_input);
			break ;
		}
		input++;
	}
	return (0);
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

int	input_error_checks(t_loop_data *loop_data)
{
	const char	*str = loop_data->trimmed_input;

	if (check_redirections(str))
		ft_printf("Input error: invalid redirection.\n");
	else if (check_operators(loop_data))
		ft_printf("Input error: invalid operator.\n");
	else if (check_open_quotes(str))
		ft_printf("Input error: open quote.\n");
	else
		return (0);
	return (1);
}
