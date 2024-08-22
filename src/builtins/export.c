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

int		builtin_export(t_ms_data *data);
void	add_env(char *key, t_ms_data *data);

int	builtin_export(t_ms_data *data)
{
	t_env	*curr_node;
	char	*key;

	key = NULL;
	if ((data->args[1] == NULL && data->args[2] == NULL) \
			|| ft_strncmp(data->args[1], "-p", 2) == 0)
	{
		curr_node = data->envp;
		while (curr_node)
			curr_node = curr_node->next;
	}
	else
		add_env(key, data);
	return (0);
}

void	add_env(char *key, t_ms_data *data)
{
	int	i;

	i = 0;
	while (data->args[++i])
	{
		if (ft_strchr(data->args[i], '='))
			set_env(&data->envp, data->args[i], \
					ft_strchr(data->args[i], '=') + 1);
		else
		{
			key = ft_strcdup(data->args[i], '=');
			if (get_env(data->envp, key))
				set_env(&data->envp, key, "");
			else
				set_env(&data->envp, key, NULL);
			free(key);
		}
	}
}
