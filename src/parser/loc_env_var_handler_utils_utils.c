/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loc_env_var_handler_utils_utils.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmikhayl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 01:45:18 by rmikhayl          #+#    #+#             */
/*   Updated: 2024/09/10 01:45:21 by rmikhayl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"

char	*expand_env_and_loc_var(char *arg, t_ms_data *data);
void	final_quote_removal(int arg_count, t_ast *command_node);
char	*get_env_variable(char *arg, t_ms_data *data);
void	handle_trailing_quote(char *arg);
char	*get_exit_status(t_ms_data *data);

void	final_quote_removal(int arg_count, t_ast *command_node)
{
	int		i;
	size_t	len;
	char	*arg;
	char	*trimmed_arg;

	i = 0;
	while (i < arg_count)
	{
		arg = command_node->args[i];
		len = ft_strlen(arg);
		if ((arg[0] == '"' && arg[len - 1] == '"') || (arg[0] == '\''
				&& arg[len - 1] == '\''))
		{
			trimmed_arg = ft_strndup(arg + 1, len - 2);
			free(command_node->args[i]);
			command_node->args[i] = trimmed_arg;
		}
		i++;
	}
}

char	*expand_env_and_loc_var(char *arg, t_ms_data *data)
{
	char	*env_value_dup;

	arg = exit_status_adj(arg);
	if (ft_strcmp(arg, "$?") == 0)
		return (get_exit_status(data));
	else if (arg[0] == '$')
	{
		handle_trailing_quote(arg);
		env_value_dup = get_env_variable(arg, data);
		return (env_value_dup);
	}
	return (ft_strdup(""));
}

char	*get_exit_status(t_ms_data *data)
{
	char	*exit_status;
	char	*exit_status_dup;

	exit_status = get_shell_variable(data->shell_variables, "?");
	exit_status_dup = ft_strdup(exit_status);
	return (exit_status_dup);
}

void	handle_trailing_quote(char *arg)
{
	if (arg[ft_strlen(arg) - 1] == '"')
		arg[ft_strlen(arg) - 1] = '\0';
}

char	*get_env_variable(char *arg, t_ms_data *data)
{
	char	*env_value;

	env_value = get_env(data->envp, arg + 1);
	if (!env_value)
		env_value = get_env(data->shell_variables, arg + 1);
	if (env_value)
		return (ft_strdup(env_value));
	return (ft_strdup(""));
}
