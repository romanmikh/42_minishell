/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmdemirk <dmdemirk@student.42london.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 17:38:25 by dmdemirk          #+#    #+#             */
/*   Updated: 2024/06/10 19:03:12 by dmdemirk         ###   ########.fr       */
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
	char	*temp;

	i = 0;
	curr_node = envp;
	while (curr_node)
	{
		i++;
		curr_node = curr_node->next;
	}
	env_array = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	curr_node = envp;
	while (curr_node)
	{
		temp = ft_strjoin(curr_node->key, "=");
		env_array[i] = ft_strjoin(temp, curr_node->value);
		free(temp);
		i++;
		curr_node = curr_node->next;
	}
	env_array[i] = NULL;
	return (env_array);
}

/**
 * The function `ft_strcdup` duplicates a string `s` until the character `c` is encountered or the end
 * of the string is reached.
 * 
 * @param s The `s` parameter in the `ft_strcdup` function is a pointer to a constant character array
 * (string) from which a new string will be duplicated up to the specified character `c`.
 * @param c The parameter `c` in the `ft_strcdup` function represents the character that will be used
 * as a delimiter. The function will copy the characters from the input string `s` until it encounters
 * this delimiter character `c`, or until the end of the string if the delimiter is not found
 * 
 * @return The function `ft_strcdup` returns a newly allocated string that is a duplicate of the input
 * string `s` up to the first occurrence of the character `c`. If memory allocation fails, it returns
 * `NULL`.
 */
 
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
