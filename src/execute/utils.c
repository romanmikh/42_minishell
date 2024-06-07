/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmdemirk <dmdemirk@student.42london.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 17:32:22 by dmdemirk          #+#    #+#             */
/*   Updated: 2024/06/04 17:48:09 by dmdemirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "env.h"
#include <stdio.h>

char	*ft_find_path(char *cmd, t_env *envp);
void	ft_free_2d_arr(char **arr);

char	*ft_find_path(char *cmd, t_env *envp)
{
	char	**path;
	char	*tmp;
	char	*tmp2;
	int		i;

	path = ft_split(get_env_value(envp, "PATH"), ':');
	int j = -1;
	while (path[++j] != NULL)
		printf("path[%d]: %s\n", j, path[j]);
	i = -1;
	while (path[++i] != NULL)
	{
		tmp = ft_strjoin(path[i], "/");
		tmp2 = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(tmp2, F_OK) == 0)
		{
			ft_free_2d_arr(path);
			return (tmp2);
		}
		free(tmp2);
	}
	ft_free_2d_arr(path);
	return (NULL);
}

void	ft_free_2d_arr(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i] != NULL)
		free(arr[i]);
	free(arr);
}
