/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmdemirk <dmdemirk@student.42london.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:31:07 by dmdemirk          #+#    #+#             */
/*   Updated: 2024/06/10 17:18:38 by dmdemirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include "shell.h"
#include "env.h"

/*
	Functionality:
		- Change the current directory
		- Update the PWD and OLDPWD environment variables
		- navigate to the home directory if no arguments are provided
		- navigate to the previous directory if ".." is provided
*/

int	builtin_cd(t_minishell_data *data)
{
	char	*target_dir;
	char	*home_dir;

	printf("builtin_cd\n");
	home_dir = get_env(data->envp, "HOME");
	target_dir = (char *)data->args[1];
	if (!target_dir)
		target_dir = home_dir;
	else if (target_dir[0] == '~')
		target_dir = ft_strjoin(home_dir, target_dir + 1);
	else if (ft_strncmp(target_dir, "..", 2) == 0)
	{
		target_dir = get_env(data->envp, "PWD");
		target_dir = ft_strcdup(target_dir, '/');
	}
	if (chdir(target_dir) != 0)
	{
		ft_putstr_fd("bash: cd: ", 2);
		perror(target_dir);
		return (1);
	}
	set_env(&data->envp, "OLDPWD", get_env(data->envp, "PWD"));
	set_env(&data->envp, "PWD", target_dir);
	return (0);
}
