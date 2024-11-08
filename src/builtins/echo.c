/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmdemirk <dmdemirk@student.42london.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:31:33 by dmdemirk          #+#    #+#             */
/*   Updated: 2024/11/08 15:15:40 by dmdemirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "exit_status.h"
#include "execute.h"

/*
Functionality:
- Print the argument
 */

int	builtin_echo(t_ms_data *data)
{
	int		newline;
	int		i;
	char	**args;

	newline = 1;
	i = 1;
	args = data->args;
	if (!data || !data->args || !data->args[0])
		return (EXIT_FAILURE);
	handle_std_io(&data->std_out, STDOUT_FILENO);
	if (args[1] && ft_strcmp(args[1], "-n") == 0)
	{
		newline = 0;
		i = 2;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], STDOUT_FILENO);
		if (args[i + 1])
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
	if (newline)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
