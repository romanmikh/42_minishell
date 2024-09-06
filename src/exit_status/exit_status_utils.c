/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmdemirk <dmdemirk@student.42london.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 11:33:18 by dmdemirk          #+#    #+#             */
/*   Updated: 2024/09/06 11:34:28 by dmdemirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exit_status.h"
#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

int	ft_perror(char *str);
int	ft_isnumber(char *str);

/**
  - @brief return error message and exit
  - 
  - @param str paste the error message
  - @return int return status:
  - 				- 1: ERROR
 */

int	ft_perror(char *str)
{
	perror (str);
	exit(EXIT_FAILURE);
}

int	ft_isnumber(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}
