/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmdemirk <dmdemirk@student.42london.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 17:20:11 by dmdemirk          #+#    #+#             */
/*   Updated: 2024/06/26 14:48:35 by dmdemirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "env.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>
#include "exit_status.h"

void	print_env_stack(t_env *envp);
int		builtin_env(t_ms_data *data);

void	print_env_stack(t_env *envp)
{
	t_env	*curr_node;

	curr_node = envp;
	while (curr_node)
	{
		ft_printf("%s=%s\n", curr_node->key, curr_node->value);
		curr_node = curr_node->next;
	}
}

int	builtin_env(t_ms_data *data)
{
	if (ft_strcmp(data->args[0], "env") == 0 && data->args[1] == NULL)
		print_env_stack(data->envp);
	else
	{
		ft_putstr_fd("env: '", STDERR_FILENO);
		ft_putstr_fd(data->args[1], STDERR_FILENO);
		ft_putstr_fd("': No such file or directory\n", STDERR_FILENO);
		set_exit_status(&data->exit_status, IS_DIRECTORY);
		set_shell_var(&data->shell_variables, "?", ft_itoa(data->exit_status));
		return (IS_DIRECTORY);
	}
	return (EXIT_SUCCESS);
}
