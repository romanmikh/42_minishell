/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_checker_helpers.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rocky <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 10:28:07 by rocky             #+#    #+#             */
/*   Updated: 2024/06/14 10:28:37 by rocky            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"

char	*trim_input(char *str)
{
	char	*trimmed_str;

	trimmed_str = ft_strtrim(str, " \t\n\r\v\f");
	if (!trimmed_str)
		return (0);
	return (trimmed_str);
}

int	valid_operator(const char **str)
{
	const char	*start;

	start = (*str)++;
	if (*start == **str)
		(*str)++;
	*str = ft_exclude_delimiters(*str, " \t\n\r\v\f");
	if (**str == '<' || **str == '>' || **str == '|' || **str == '\0')
		return (0);
	return (1);
}
