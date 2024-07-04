/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmdemirk <dmdemirk@student.42london.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 17:32:22 by dmdemirk          #+#    #+#             */
/*   Updated: 2024/06/26 15:27:16 by dmdemirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "env.h"
#include <stdio.h>
#include "shell.h"

char	*ft_find_path(char *cmd, t_env *envp);
void	ft_free_2d_arr(char **arr);
int		ft_perror(char *str);
void	close_fds(int fds[2]);
void	handle_temp_fd(t_minishell_data *data);

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

int	ft_perror(char *str)
{
	perror (str);
	exit(EXIT_FAILURE);
}

void	close_fds(int fds[2])
{
	close(fds[0]);
	close(fds[1]);
}

void	handle_temp_fd(t_minishell_data *data)
{
	if (data->temp_fd != -1)
	{
		close(data->temp_fd);
		data->temp_fd = -1;
	}
}
