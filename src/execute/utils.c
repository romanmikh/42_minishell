/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmdemirk <dmdemirk@student.42london.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 17:32:22 by dmdemirk          #+#    #+#             */
/*   Updated: 2024/06/17 11:08:49 by dmdemirk         ###   ########.fr       */
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
	char	*tmp_slash;
	char	*tmp_full_path;
	int		i;

	path = ft_split(get_env(envp, "PATH"), ':');
	i = -1;
	while (path[++i] != NULL)
	{
		tmp_slash = ft_strjoin(path[i], "/");
		tmp_full_path = ft_strjoin(tmp_slash, cmd);
		free(tmp_slash);
		if (access(tmp_full_path, F_OK) == 0)
		{
			ft_free_2d_arr(path);
			return (tmp_full_path);
		}
		free(tmp_full_path);
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
