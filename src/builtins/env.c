/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmdemirk <dmdemirk@student.42london.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:32:34 by dmdemirk          #+#    #+#             */
/*   Updated: 2024/06/04 12:21:02 by dmdemirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "shell.h"
#include "env.h"

void print_env_stack(t_env *envp)
{
	t_env	*curr_node;

	curr_node = envp;
	while (curr_node)
	{
		printf("%s=%s\n", curr_node->key, curr_node->value);
		curr_node = curr_node->next;
	}
}


int	builtin_env(t_minishell_data *data)
{
	int	i;

	i = -1;
	printf("\nbuiltin_env\n");
	printf("Print envp:\n");
	print_env_stack(data->envp);
	return (0);
}
