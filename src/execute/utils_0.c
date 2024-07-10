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
void	close_fds(int in, int out);
void	handle_temp_fd(t_minishell_data *data);

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

/**
- @brief clean up 2d array
- 
- @param arr simple two dimensional array
 */

void	ft_free_2d_arr(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i] != NULL)
		free(arr[i]);
	free(arr);
}

/**
- @brief return error message and exit
- 
- @param str paste the error message
- @return int return status:
- 				- 1: EXIT_FAILURE
 */

int	ft_perror(char *str)
{
	perror (str);
	exit(EXIT_FAILURE);
}

/**
- @brief close two file descriptors
- 
- @param fds file descriptors
 */

void	close_fds(int in, int out)
{
	close(in);
	close(out);
}

/**
- @brief close temporary input/output file descriptors and reset them to -1
- @param data minishell structure
 */

void	handle_io_fd(t_minishell_data *data)
{
	if (data->std_in != -1 && data->std_out != -1)
	{
		close(data->std_in);
		close(data->std_out);
		data->std_in = -1;
		data->std_out = -1;
	}
}
