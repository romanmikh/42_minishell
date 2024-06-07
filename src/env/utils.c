/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmdemirk <dmdemirk@student.42london.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 17:38:25 by dmdemirk          #+#    #+#             */
/*   Updated: 2024/06/07 17:38:26 by dmdemirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

void	init_env(t_env **data_envp, char **envp);
char    *ft_strcdup(const char *s, int c);
void	add_env_node(t_env **data_envp, char *line);

void	init_env(t_env **data_envp, char **envp)
{
	int	i;

	i = -1;
	while (envp[++i])
		add_env_node(data_envp, envp[i]);
}

char *ft_strcdup(const char *s, int c)
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

void	add_env_node(t_env **data_envp, char *line)
{
    t_env	*new_node;
    t_env	*curr_node;
    char	*key;
    char	*value;

    new_node = (t_env *)malloc(sizeof(t_env));
    if (!new_node)
        return ;
    key = ft_strcdup(line, '=');
    value = ft_strchr(line, '=') + 1;
    new_node->key = key;
    printf("key: %s\n", new_node->key);
    new_node->value = value;
    printf("value: %s\n", new_node->value);
    new_node->next = NULL;
    if (*data_envp == NULL)
    {
        *data_envp = new_node;
        return ;
    }
    curr_node = *data_envp;
    while (curr_node->next != NULL)
        curr_node = curr_node->next;
    curr_node->next = new_node;
}

