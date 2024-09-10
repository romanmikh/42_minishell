/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_0.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmdemirk <dmdemirk@student.42london.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 17:32:22 by dmdemirk          #+#    #+#             */
/*   Updated: 2024/09/09 13:01:32 by dmdemirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include "shell.h"
#include "execute.h"

int		ft_perror(char *str);
void	close_fds(int in, int out);
void	handle_temp_fd(t_ms_data *data);

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

void	handle_io_fd(t_ms_data *data)
{
	if (data->std_in != -1 && data->std_out != -1)
	{
		close(data->std_in);
		close(data->std_out);
		data->std_in = -1;
		data->std_out = -1;
	}
}

void	handle_std_io(int *std_io, int std_fileno)
{
	if (*std_io == -1)
		*std_io = dup(std_fileno);
	else
		dup2(*std_io, std_fileno);
}
