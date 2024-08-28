/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmdemirk <dmdemirk@student.42london.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:31:07 by dmdemirk          #+#    #+#             */
/*   Updated: 2024/07/11 16:06:37 by dmdemirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include "shell.h"
#include "env.h"

/*
   - Functionality:
   - Change the current directory
   - Update the PWD and OLDPWD environment variables
   - If no argument is provided, change to the HOME directory
   - If the target directory does not exist, print an error message
 */

int	builtin_cd(t_ms_data *data)
{
	char	*target_dir;
	char	*home_dir;
	char	cwd[4096];

	ft_printf("builtin_cd\n");
	home_dir = get_env(data->envp, "HOME");
	target_dir = (char *)data->args[1];
	if (!target_dir)
		target_dir = home_dir;
	if (chdir(target_dir) != 0)
	{
		ft_putstr_fd("bash: cd: ", 2);
		perror(target_dir);
		return (1);
	}
	set_env(&data->envp, "OLDPWD", get_env(data->envp, "PWD"));
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		set_env(&data->envp, "PWD", cwd);
	return (0);
}
