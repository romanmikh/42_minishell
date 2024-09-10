/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmdemirk <dmdemirk@student.42london.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:31:07 by dmdemirk          #+#    #+#             */
/*   Updated: 2024/09/09 13:09:59 by dmdemirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include "shell.h"
#include "env.h"
#include "execute.h"
#include "exit_status.h"

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
	char	*error_message;
	char	cwd[4096];

	home_dir = get_env(data->envp, "HOME");
	target_dir = (char *)data->args[1];
	if (!target_dir)
		target_dir = home_dir;
	if (chdir(target_dir) == -1)
	{
		error_message = ft_strjoin("cd: ", target_dir);
		if (errno == EACCES)
			exit_status_handler(data, PERMISSION_DENIED, error_message);
		if (errno == ENOENT)
			exit_status_handler(data, IS_DIRECTORY, error_message);
		free(error_message);
		return (EXIT_FAILURE);
	}
	set_env(&data->envp, "OLDPWD", get_env(data->envp, "PWD"));
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		set_env(&data->envp, "PWD", cwd);
	return (EXIT_SUCCESS);
}
