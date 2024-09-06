/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmdemirk <dmdemirk@student.42london.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 11:10:33 by dmdemirk          #+#    #+#             */
/*   Updated: 2024/09/06 12:01:53 by dmdemirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include <unistd.h>
#include "libft.h"
#include <stdio.h>
#include "exit_status.h"

/*
Functionality:
- Print the current working directory
 */

int	builtin_pwd(t_ms_data *data)
{
	char	cwd[4096];

	(void)data;
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		ft_putendl_fd(cwd, STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
