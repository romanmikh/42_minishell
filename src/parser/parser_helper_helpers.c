/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helper_helpers.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rocky <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 20:36:33 by rocky             #+#    #+#             */
/*   Updated: 2024/08/28 20:36:39 by rocky            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"

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
		if ((arg[0] == '"' && arg[len - 1] == '"') || (arg[0] == '\'' \
			&& arg[len - 1] == '\''))
		{
			trimmed_arg = ft_strndup(arg + 1, len - 2);
			free(command_node->args[i]);
			command_node->args[i] = trimmed_arg;
		}
		i++;
	}
}

char	*expand_env_var(char *arg, t_ms_data *data)
{
	char	*env_value;

	if (ft_strcmp(arg, "$?") == 0)
		return (ft_itoa(data->exit_status));
	else if (arg[0] == '$')
	{
		if (arg[ft_strlen(arg) - 1] == '"')
			arg[ft_strlen(arg) - 1] = '\0';
		env_value = get_env(data->envp, arg + 1);
		if (env_value)
			return (ft_strdup(env_value));
	}
	return (ft_strdup(arg));
}

void	post_process_command_args(t_ast *command_node, int arg_count, \
			t_ms_data *data)
{
	int		i;
	char	*arg;
	char	*processed_arg;

	i = 0;
	while (i < arg_count)
	{
		arg = command_node->args[i];
		processed_arg = NULL;
		if (arg[0] == '$' || (arg[0] == '"' && arg[1] == '$'))
		{
			if (arg[0] == '"')
				processed_arg = expand_env_var(arg + 1, data);
			else
				processed_arg = expand_env_var(arg, data);
		}
		else if (arg[0] == '\'')
			processed_arg = ft_strdup(arg);
		else
			processed_arg = ft_strdup(arg);
		free(command_node->args[i]);
		command_node->args[i] = processed_arg;
		i++;
	}
	final_quote_removal(arg_count, command_node);
}
