/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmdemirk <dmdemirk@student.42london.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 11:10:03 by dmdemirk          #+#    #+#             */
/*   Updated: 2024/09/06 12:01:39 by dmdemirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "env.h"
#include "libft.h"
#include <unistd.h>
#include "exit_status.h"

#include <stdio.h>

/*
   todo
   set the exit status to ERROR if the variable is not a valid identifier
Functionality:
- Unset the environment variable
- Return ERROR if the variable is not a valid identifier    
 */

int	builtin_unset(t_ms_data *data)
{
	int		i;
	char	*key;

	i = 0;
	while (data->args[++i])
	{
		key = data->args[i];
		if (unset_env(&data->envp, key) == -1)
		{
			return (EXIT_SUCCESS);
		}
	}
	return (EXIT_SUCCESS);
}
