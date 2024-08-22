/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmdemirk <dmdemirk@student.42london.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 11:10:03 by dmdemirk          #+#    #+#             */
/*   Updated: 2024/06/17 11:10:25 by dmdemirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "env.h"
#include "libft.h"
#include <unistd.h>

/*
   todo
   set the exit status to 1 if the variable is not a valid identifier
Functionality:
- Unset the environment variable
- Return 1 if the variable is not a valid identifier    
 */

int	builtin_unset(t_ms_data *data)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	while (data->args[++i])
	{
		if (unset_env(&data->envp, data->args[i]) == -1)
		{
			ft_putstr_fd("bash: unset: `", STDERR_FILENO);
			ft_putstr_fd(data->args[i], STDERR_FILENO);
			ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
			ret = 1;
		}
	}
	data->exit_status = ret;
	return (ret);
}
