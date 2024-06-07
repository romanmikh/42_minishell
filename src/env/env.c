/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmdemirk <dmdemirk@student.42london.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 17:20:11 by dmdemirk          #+#    #+#             */
/*   Updated: 2024/06/07 17:20:13 by dmdemirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "env.h"
#include "libft.h"
#include <stdlib.h>

char *get_env_value(t_env *envp, char *key);
char **env_to_array(t_env *envp);

char *get_env_value(t_env *envp, char *key)
{
    t_env *curr_node;

    curr_node = envp;
    while (curr_node)
    {
        if (ft_strcmp(curr_node->key, key) == 0)
            return (curr_node->value);
        curr_node = curr_node->next;
    }
    return (NULL);
}

char **env_to_array(t_env *envp)
{
    t_env *curr_node;
    char **env_array;
    int i;

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