/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_variables.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmdemirk <dmdemirk@student.42london.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 11:51:16 by dmdemirk          #+#    #+#             */
/*   Updated: 2024/09/06 11:51:54 by dmdemirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "env.h"
#include "libft.h"
#include "tokens.h"
#include <stddef.h>

int		handle_add_set_shell_variable(t_env **shell_var, char *line);
int		handle_get_shell_variable(t_ms_data *data, const char *key);
int		handle_shell_variable(t_ast *node, t_ms_data *data);
void	shell_variable_update(t_ms_data *data, int status);

int	handle_add_set_shell_variable(t_env **shell_var, char *line)
{
	char	*key;
	char	*value;

	key = NULL;
	value = NULL;
	if (*shell_var == NULL)
		add_shell_var_node(shell_var, line);
	else
	{
		key = ft_strcdup(line, '=');
		value = ft_strchr(line, '=') + 1;
		set_shell_var(shell_var, key, value);
		printf("value: %s\n", get_env(*shell_var, key));
		free(key);
	}
	return (0);
}

int	handle_get_shell_variable(t_ms_data *data, const char *key)
{
	char	*value;
	t_env	*shell_var;

	shell_var = data->shell_variables;
	value = get_env(shell_var, key);
	if (value)
	{
		ft_putstr_fd(value, data->std_out);
		ft_putstr_fd("\n", data->std_out);
		return (0);
	}
	return (-1);
}

int	handle_shell_variable(t_ast *node, t_ms_data *data)
{
	if (node->left && node->right == NULL)
		return (handle_get_shell_variable(data, node->args[0]));
	return (-1);
}

void	shell_variable_update(t_ms_data *data, int status)
{
	data->exit_status = status;
	set_shell_var(&data->shell_variables, "?", ft_itoa(status));
}
