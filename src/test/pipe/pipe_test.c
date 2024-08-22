/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmdemirk <dmdemirk@student.42london.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 11:03:20 by dmdemirk          #+#    #+#             */
/*   Updated: 2024/07/11 18:44:58 by dmdemirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <assert.h>
#include <stdio.h>
#include "shell.h"
#include "pipe.h"
#include "libft.h"

void	builtin_pipe_test(t_ms_data *data);
void	pipe_tests(t_ms_data *data);

void	pipe_tests(t_ms_data *data)
{
	printf("\nPIPE TESTS\n");
	builtin_pipe_test(data);
	printf("\033[0m");
	printf("\033[0;32m");
	printf("pipe_test    -> OK\n");
	printf("\033[0m");
}

void	builtin_pipe_test(t_ms_data *data)
{
	data->args = ft_split("ls -l | wc -l", ' ');
	builtin_pipe(node, data);
	assert(data->args != NULL);
}
