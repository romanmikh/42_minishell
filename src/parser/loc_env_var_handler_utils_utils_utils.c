/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loc_env_var_handler_utils_utils_utils.c            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmikhayl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 01:45:50 by rmikhayl          #+#    #+#             */
/*   Updated: 2024/09/10 01:45:52 by rmikhayl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"

char	*exit_status_adj(char *arg);
int		is_in_single_quotes(char *arg);
char	*str_start_adj(char *arg);
char	*tmp_adj(char *arg);
char	*append_literal(char **start, char *processed_arg);

char	*exit_status_adj(char *arg)
{
	if (ft_strcmp(arg, "$") == 0)
		return ("$?");
	return (arg);
}

int	is_in_single_quotes(char *arg)
{
	int	len;

	if (!arg || arg[0] != '\'')
		return (0);
	len = 0;
	while (arg[len] != '\0')
		len++;
	if (arg[len - 1] == '\'')
		return (1);
	return (0);
}

char	*str_start_adj(char *arg)
{
	if (!ft_strcmp(arg, "?") || !ft_strcmp(arg, "?\""))
		return ("");
	else if (!ft_strcmp(arg, "?\'"))
		return ("\'");
	return (arg);
}

char	*tmp_adj(char *arg)
{
	char	*ptr;
	char	*tmp_adj_dup;

	if (*arg == '\"')
	{
		ptr = arg + 1;
		while (*ptr)
		{
			if (!ft_isdigit(*ptr))
				return (arg);
			ptr++;
		}
		tmp_adj_dup = ft_strdup(arg + 1);
		free(arg);
		return (tmp_adj_dup);
	}
	tmp_adj_dup = ft_strdup(arg);
	free(arg);
	return (tmp_adj_dup);
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
