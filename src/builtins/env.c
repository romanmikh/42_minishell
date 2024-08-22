/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmdemirk <dmdemirk@student.42london.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:32:34 by dmdemirk          #+#    #+#             */
/*   Updated: 2024/06/11 16:44:41 by dmdemirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "shell.h"
#include "env.h"
#include "libft.h"

/*
	Functionality:
		- Print the environment
*/

void	print_env_stack(t_env *envp);
int		builtin_env(t_ms_data *data);

void	print_env_stack(t_env *envp)
{
	t_env	*curr_node;

	curr_node = envp;
	while (curr_node)
	{
		printf("%s=%s\n", curr_node->key, curr_node->value);
		curr_node = curr_node->next;
	}
}

int	builtin_env(t_ms_data *data)
{
	printf("\nbuiltin_env\n");
	if (ft_strcmp(data->args[0], "env") == 0 && data->args[1] == NULL)
		print_env_stack(data->envp);
	return (0);
}
