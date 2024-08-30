/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmdemirk <dmdemirk@student.42london.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 11:10:52 by dmdemirk          #+#    #+#             */
/*   Updated: 2024/06/17 15:34:56 by dmdemirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"
#include <stdlib.h>
#include "shell.h"
#include <stdio.h>

/*
Functionalities:
- If no arguments are passed or "-p", print all environment variables
- If arguments are passed, set the environment variables
 */

int			      builtin_export(t_ms_data *data);
static  void	add_env(t_ms_data *data);

int	builtin_export(t_ms_data *data)
{
	t_env	*curr_node;

	if ((data->args[1] == NULL) \
			|| ft_strncmp(data->args[1], "-p", 1) == 0)
	{
		curr_node = data->envp;
		while (curr_node)
		{
			if (!ft_strcmp(curr_node->value, ""))
				printf("declare -x %s\n", curr_node->key);
			else
				printf("declare -x %s=\"%s\"\n", curr_node->key, curr_node->value);
			curr_node = curr_node->next;
		}
	}
	else 
		add_env(data);
	return (0);
}


static void	add_env(t_ms_data *data)
{
	int		i;
	char*	key;
	char*	curr_arg;

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
