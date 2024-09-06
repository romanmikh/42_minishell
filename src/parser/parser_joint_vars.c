/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_joint_vars.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmikhayl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 16:46:53 by rmikhayl          #+#    #+#             */
/*   Updated: 2024/09/04 16:46:57 by rmikhayl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tokens.h>

char	*expand_variable(char **start, t_ms_data *data)
{
	char	*var_name;
	char	*expanded_var;
	char	*var_start;

	var_start = *start;
	(*start)++;
	while (**start != '\0' && (ft_isalnum(**start) || **start == '_'))
		(*start)++;
	var_name = ft_substr(var_start, 0, *start - var_start);
	expanded_var = expand_env_and_loc_var(var_name, data);
	free(var_name);
	return (expanded_var);
}

char	*append_literal(char **start, char *processed_arg)
{
	char	*literal_part;
	char	*literal_start;
	char	*tmp;

	literal_start = *start;
	while (**start != '\0' && **start != '$')
		(*start)++;
	literal_part = ft_substr(literal_start, 0, *start - literal_start);
	tmp = ft_strjoin(processed_arg, literal_part);
	free(literal_part);
	free(processed_arg);
	return (tmp);
}

char	*process_argument(char *arg, t_ms_data *data)
{
	char	*start;
	char	*processed_arg;
	char	*tmp;
	char	*expanded_var;

	processed_arg = ft_strdup("");
	start = arg;
	while (*start != '\0')
	{
		if (*start == '$')
		{
			expanded_var = expand_variable(&start, data);
			if (expanded_var != NULL)
			{
				tmp = ft_strjoin(processed_arg, expanded_var);
				free(processed_arg);
				processed_arg = tmp;
				free(expanded_var);
			}
		}
		else
			processed_arg = append_literal(&start, processed_arg);
	}
	return (processed_arg);
}
