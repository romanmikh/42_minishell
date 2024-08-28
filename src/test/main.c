/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmdemirk <dmdemirk@student.42london.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 16:48:02 by dmdemirk          #+#    #+#             */
/*   Updated: 2024/06/17 11:04:24 by dmdemirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"
#include "shell.h"
#include <stdio.h>
#include <stdlib.h>

int	main(int argc, char **argv, char **envp)
{
	t_ms_data	data;

	if (argc > 1)
	{
		ft_printf("Usage: %s\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	pipe_tests(&data);
	env_tests(&data, envp);
	return (0);
}
