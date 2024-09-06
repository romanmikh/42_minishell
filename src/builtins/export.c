/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmdemirk <dmdemirk@student.42london.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 11:10:52 by dmdemirk          #+#    #+#             */
/*   Updated: 2024/09/06 13:45:43 by dmdemirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"
#include <stdlib.h>
#include "shell.h"
#include <stdio.h>
#include "exit_status.h"

/*
Functionalities:
- If no arguments are passed or "-p", print all environment variables
- If arguments are passed, set the environment variables
 */

int				builtin_export(t_ms_data *data);
static void		print_env(t_env *env);
static void		add_env(t_ms_data *data);

int	builtin_export(t_ms_data *data)
{
	if (data->args == NULL || data->args[1] == NULL)
	{
		print_env(data->envp);
		return (EXIT_SUCCESS);
	}
	if (ft_strcmp(data->args[1], "-p") != 0 && data->args[1][0] == '-')
	{
		exit_status_handler(data, INVALID_OPTION, \
				ft_strjoin("export: ", data->args[1]));
		ft_putendl_fd("export: usage: export [-p]" \
				"[name[=value] ...] or export -p", STDERR_FILENO);
		return (INVALID_OPTION);
	}
	else if (ft_strcmp(data->args[1], "-p") == 0)
	{
		print_env(data->envp);
		return (EXIT_SUCCESS);
	}
	add_env(data);
	return (EXIT_SUCCESS);
}

static void	print_env(t_env *env)
{
	t_env	*curr_node;

	curr_node = env;
	while (curr_node)
	{
		if (!ft_strcmp(curr_node->value, ""))
			printf("declare -x %s\n", curr_node->key);
		else
			printf("declare -x %s=\"%s\"\n", curr_node->key, curr_node->value);
		curr_node = curr_node->next;
	}
}

static void	add_env(t_ms_data *data)
{
	int		i;
	char	*key;
	char	*curr_arg;

	i = 0;
	key = NULL;
	curr_arg = NULL;
	while (data->args[++i])
	{
		if (ft_strchr(data->args[i], '='))
		{
			curr_arg = data->args[i];
			key = ft_strcdup(curr_arg, '=');
			set_env(&data->envp, key, \
					ft_strchr(curr_arg, '=') + 1);
		}
		else
		{
			curr_arg = data->args[i];
			key = curr_arg;
			set_env(&data->envp, key, "");
		}
	}
}
