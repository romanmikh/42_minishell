/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmdemirk <dmdemirk@student.42london.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 11:10:52 by dmdemirk          #+#    #+#             */
/*   Updated: 2024/06/17 11:15:10 by dmdemirk         ###   ########.fr       */
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
/*
int	builtin_export(t_minishell_data *data)
{
	t_env	*curr_node;
	char	*key;
	int		i;

	i = 0;
	if ((data->args[1] == NULL && data->args[2] == NULL) \
			|| ft_strncmp(data->args[1], "-p", 2) == 0)
	{
		curr_node = data->envp;
		while (curr_node)
			curr_node = curr_node->next;
	}
	else
	{
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
	return (0);

}
*/
