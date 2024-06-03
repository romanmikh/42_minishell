/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmdemirk <dmdemirk@student.42london.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:31:33 by dmdemirk          #+#    #+#             */
/*   Updated: 2024/06/03 16:38:36 by dmdemirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	builtin_echo(const char **argv)
{
	int	newline;
	int	i;

	newline = 1;
	if (ft_strcmp(argv[1], "-n") == 0)
	{
		newline = 0;
		argv++;
	}
	i = -1;
	while (*argv++)
	{
		write(1, argv[i], ft_strlen(argv[i]));
		i++;
	}
	if (newline)
		write(1, "\n", 1);
	return (0);
}
