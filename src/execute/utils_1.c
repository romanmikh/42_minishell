/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmdemirk <dmdemirk@student.42london.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 18:11:06 by dmdemirk          #+#    #+#             */
/*   Updated: 2024/09/09 13:00:02 by dmdemirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "env.h"
#include "execute.h"

char		*ft_find_path(char *cmd, t_env *envp);
static void	relative_path_handle(char *cmd, char *path, char **tmp_full_path);

/**
  - @brief function find the full path of the executed command
  - 
  - @param cmd string from the first argument
  - @param envp structure with environment variables
  - @return char* returns the full path of the command
 */

char	*ft_find_path(char *cmd, t_env *envp)
{
	char	**path;
	char	*tmp_full_path;
	int		i;

	path = ft_split(get_env(envp, "PATH"), ':');
	i = -1;
	while (path[++i] != NULL)
	{
		if (ft_strncmp(cmd, "/", 1) != 0)
			relative_path_handle(cmd, path[i], &tmp_full_path);
		else
			tmp_full_path = ft_strdup(cmd);
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

static void	relative_path_handle(char *cmd, char *path, char **tmp_full_path)
{
	char	*tmp_slash;

	tmp_slash = ft_strjoin(path, "/");
	*tmp_full_path = ft_strjoin(tmp_slash, cmd);
	free(tmp_slash);
}
