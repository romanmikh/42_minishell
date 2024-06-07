/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmdemirk <dmdemirk@student.42london.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:31:07 by dmdemirk          #+#    #+#             */
/*   Updated: 2024/06/04 12:21:28 by dmdemirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include "shell.h"
#include "env.h"

int	builtin_cd(t_minishell_data *data)
{
	char	*target_dir;
	char	*home_dir;

	printf("builtin_cd\n");
	home_dir = getenv("HOME");
	target_dir = (char *)data->args[1];
	if (!target_dir)
		target_dir = home_dir;
	else if (target_dir[0] == '~')
		target_dir = ft_strjoin(home_dir, target_dir + 1);
	// set_env(data, "OLDPWD", getenv("PWD"));
	// set_env(data, "PWD", target_dir);
	if (chdir(target_dir) != 0)
	{
		perror("cd");
		return (1);
	}
	return (0);
}
