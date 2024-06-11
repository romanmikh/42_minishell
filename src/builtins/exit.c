/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmdemirk <dmdemirk@student.42london.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:32:42 by dmdemirk          #+#    #+#             */
/*   Updated: 2024/06/11 16:47:39 by dmdemirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

/*
todo
Add cleanup functions
Add functionality to handle exit status
*/

int	builtin_exit(t_minishell_data *data)
{
	const char	*message;
	
	printf("\nbuiltin_exit\n");
	message = "exit\n";
	write(STDOUT_FILENO, message, ft_strlen(message));

	exit(data->exit_status);
}
