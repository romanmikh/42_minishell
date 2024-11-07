/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmdemirk <dmdemirk@student.42london.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 17:20:11 by dmdemirk          #+#    #+#             */
/*   Updated: 2024/09/09 13:08:55 by dmdemirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

void	init_env(t_env **data_envp, char **envp);
void	add_env_node(t_env **data_envp, char *line);
char	*get_env(t_env *envp, const char *key);
void	set_env(t_env **env, const char *key, const char *value);
int		unset_env(t_env **env, const char *name);

char	*ft_remove_all_edge_quotes(char *str, char quote_type)
{
	int		start_quotes;
	int		end_quotes;
	int		len;
	char	*new_str;

	len = ft_strlen(str);
	start_quotes = 0;
	while (str[start_quotes] == quote_type)
		start_quotes++;
	end_quotes = 0;
	while (len - end_quotes - 1 >= 0 && str[len - end_quotes - 1] == quote_type)
		end_quotes++;
	if (start_quotes > 0 && start_quotes == end_quotes)
	{
		new_str = ft_strndup(str + start_quotes, len - 2 * start_quotes);
		return (new_str);
	}
	return (ft_strdup(str));
}

void	init_env(t_env **data_envp, char **envp)
{
	int	i;

	i = -1;
	while (envp[++i])
		add_env_node(data_envp, envp[i]);
}

void	add_env_node(t_env **data_envp, char *line)
{
	t_env	*new_node;
	char	*eq_pos;
	t_env	*curr;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return ;
	eq_pos = ft_strchr(line, '=');
	if (!eq_pos)
		return ;
	new_node->key = ft_strndup(line, eq_pos - line);
	new_node->value = ft_strdup(eq_pos + 1);
	new_node->next = NULL;
	if (!*data_envp)
		*data_envp = new_node;
	else
	{
		curr = *data_envp;
		while (curr->next)
			curr = curr->next;
		curr->next = new_node;
	}
}

char	*get_env(t_env *envp, const char *key)
{
	t_env	*curr_node;

	curr_node = envp;
	while (curr_node)
	{
		if (ft_strcmp(curr_node->key, key) == 0)
			return (curr_node->value);
		curr_node = curr_node->next;
	}
	return (NULL);
}

void	set_env(t_env **env, const char *key, const char *value)
{
	t_env	*current;
	t_env	*new_env;
	char	*modified_value;
	char	*temp;

	current = *env;
	modified_value = NULL;
	if (value[0] != '\0')
	{
		modified_value = ft_remove_all_edge_quotes((char *)value, '\"');
		temp = modified_value;
		modified_value = ft_remove_all_edge_quotes(modified_value, '\'');
		free(temp);
	}
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
	new_env = malloc(sizeof(t_env));
	new_env->key = ft_strdup(key);
	new_env->value = modified_value;
	new_env->next = *env;
	*env = new_env;
}

int	unset_env(t_env **env, const char *key)
{
	t_env	*current;
	t_env	*prev;

	current = *env;
	prev = NULL;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			if (prev)
				prev->next = current->next;
			else
				*env = current->next;
			free(current->key);
			free(current->value);
			free(current);
			return (0);
		}
		prev = current;
		current = current->next;
	}
	return (-1);
}
