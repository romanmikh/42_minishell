/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmdemirk <dmdemirk@student.42london.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 17:38:25 by dmdemirk          #+#    #+#             */
/*   Updated: 2024/06/10 17:23:25 by dmdemirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "env.h"
#include "libft.h"
#include <stdlib.h>

char	**env_to_array(t_env *envp);
char	*ft_strcdup(const char *s, int c);
void	free_env(t_env *envp);

char	**env_to_array(t_env *envp)
{
	t_env	*curr_node;
	char	**env_array;
	int		i;

	i = 0;
	curr_node = envp;
	while (curr_node)
	{
		i++;
		curr_node = curr_node->next;
	}
	env_array = (char **)malloc(sizeof(char *) * (i + 1));
	if (!env_array)
		return (NULL);
	i = 0;
	curr_node = envp;
	while (curr_node)
	{
		env_array[i] = ft_strjoin(curr_node->key, "=");
		env_array[i] = ft_strjoin(env_array[i], curr_node->value);
		i++;
		curr_node = curr_node->next;
	}
	env_array[i] = NULL;
	return (env_array);
}

char	*ft_strcdup(const char *s, int c)
{
	char	*str;
	size_t	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	str = (char *)malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != c)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

void	free_env(t_env *envp)
{
	t_env	*curr_node;
	t_env	*next_node;

	curr_node = envp;
	while (curr_node)
	{
		next_node = curr_node->next;
		free(curr_node->key);
		free(curr_node->value);
		free(curr_node);
		curr_node = next_node;
	}
}
