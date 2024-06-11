/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmdemirk <dmdemirk@student.42london.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 16:48:02 by dmdemirk          #+#    #+#             */
/*   Updated: 2024/06/10 16:48:28 by dmdemirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"
#include "shell.h"
#include <stdio.h>

int	main(int argc, char **argv, char **envp)
{
	t_minishell_data	data;

	argc = 0;
	argv = (void *)0;
	env_tests(&data, envp);
	return (0);
}
