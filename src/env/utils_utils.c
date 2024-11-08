/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmikhayl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 15:40:30 by rmikhayl          #+#    #+#             */
/*   Updated: 2024/11/08 15:40:34 by rmikhayl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

char	*ft_remove_all_edge_quotes(char *str, char quote_type);

static char	*remove_quotes(const char *value)
{
	char	*temp;
	char	*result;

	temp = ft_remove_all_edge_quotes((char *)value, '\"');
	result = ft_remove_all_edge_quotes(temp, '\'');
	free(temp);
	return (result);
}

void	add_new_env(t_env **env, const char *key, char *modified_value)
{
	t_env	*new_env;

	new_env = malloc(sizeof(t_env));
	if (!new_env)
		return ;
	new_env->key = ft_strdup(key);
	new_env->value = modified_value;
	new_env->next = *env;
	*env = new_env;
}

void	set_env(t_env **env, const char *key, const char *value)
{
	t_env	*current;
	char	*modified_value;

	current = *env;
	modified_value = NULL;
	if (value[0] != '\0')
		modified_value = remove_quotes(value);
	else
		modified_value = ft_strdup(value);
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			free(current->value);
			current->value = modified_value;
			return ;
		}
		current = current->next;
	}
	add_new_env(env, key, modified_value);
}
