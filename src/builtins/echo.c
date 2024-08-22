/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmdemirk <dmdemirk@student.42london.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:31:33 by dmdemirk          #+#    #+#             */
/*   Updated: 2024/07/11 17:57:16 by dmdemirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

/*
	Functionality:
		- Print the argument
*/

int	builtin_echo(t_ms_data *data)
{
	int	newline;
	int	i;

	newline = 1;
	if (data->args[1] && (ft_strcmp(data->args[1], "-n") == 0))
	{
		newline = 0;
		data->args++;
	}
	i = 0;
	while (data->args[++i])
	{
		write(1, data->args[i], ft_strlen(data->args[i]));
		if (data->args[i + 1])
			write(1, " ", 1);
	}
	if (newline)
		write(1, "\n", 1);
	return (0);
}
