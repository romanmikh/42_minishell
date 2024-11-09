/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loc_env_var_handler_utils_utils_utils_uti          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmikhayl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 12:32:24 by rmikhayl          #+#    #+#             */
/*   Updated: 2024/11/09 12:32:26 by rmikhayl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"

char	**initialize_result_array(int *count)
{
	char	**result;

	*count = 0;
	result = malloc(sizeof(char *));
	if (!result)
		return (NULL);
	return (result);
}

int	toggle_quotes(int in_quotes, char current_char)
{
	if (current_char == '"' || current_char == '\'')
		return (!in_quotes);
	return (in_quotes);
}

char	**add_segment_on_delimiter(char **result, char **start, \
				char *str, int *count)
{
	result = ft_add_segment(result, *start, str - *start, count);
	*start = str + 1;
	return (result);
}

char	**finalize_result_array(char **result, int count)
{
	char	**temp;

	temp = realloc(result, sizeof(char *) * (count + 1));
	if (!temp)
	{
		free(result);
		return (NULL);
	}
	result = temp;
	result[count] = NULL;
	return (result);
}
