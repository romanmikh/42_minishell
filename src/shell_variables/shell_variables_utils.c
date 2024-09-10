/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_variables_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmdemirk <dmdemirk@student.42london.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 11:52:02 by dmdemirk          #+#    #+#             */
/*   Updated: 2024/09/09 12:51:11 by dmdemirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "env.h"
#include "libft.h"
#include <stddef.h>
#include <stdlib.h>

#include <stdio.h>

void	set_shell_var(t_env **shell_var, const char *key, const char *value);
void	add_shell_var_node(t_env **shell_var, const char *line);
char	*get_shell_variable(t_env *shell_var, const char *key);
void	free_shell_var_list(t_env *shell_var);

void	add_shell_var_node(t_env **shell_var, const char *line)
{
	char	*key;
	char	*value;
	t_env	*new_node;
	t_env	*curr_node;

	if (!shell_var || !line)
		return ;
	key = ft_strcdup(line, '=');
	value = ft_strchr(line, '=') + 1;
	new_node = (t_env *)malloc(sizeof(t_env));
	new_node->key = ft_strdup(key);
	free(key);
	new_node->value = ft_strdup(value);
	new_node->next = NULL;
	if (*shell_var == NULL)
		*shell_var = new_node;
	else
	{
		curr_node = *shell_var;
		while (curr_node->next != NULL)
			curr_node = curr_node->next;
		curr_node->next = new_node;
	}
}

void	set_shell_var(t_env **shell_var, const char *key, const char *value)
{
	t_env	*current;
	t_env	*new_env;

	current = *shell_var;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			free(current->value);
			current->value = ft_strdup(value);
			return ;
		}
		current = current->next;
	}
	new_env = malloc(sizeof(t_env));
	new_env->key = ft_strdup(key);
	new_env->value = ft_strdup(value);
	new_env->next = *shell_var;
	*shell_var = new_env;
}

char	*get_shell_variable(t_env *shell_var, const char *key)
{
	t_env	*curr_node;

	curr_node = shell_var;
	while (curr_node)
	{
		if (ft_strcmp(curr_node->key, key) == 0)
			return (curr_node->value);
		curr_node = curr_node->next;
	}
	return (NULL);
}

void	free_shell_var_list(t_env *shell_var)
{
	t_env	*curr_node;
	t_env	*next_node;

	curr_node = shell_var;
	while (curr_node)
	{
		next_node = curr_node->next;
		free(curr_node->key);
		free(curr_node->value);
		free(curr_node);
		curr_node = next_node;
	}
}
