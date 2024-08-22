/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmdemirk <dmdemirk@student.42london.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:34:46 by dmdemirk          #+#    #+#             */
/*   Updated: 2024/07/11 14:59:38 by dmdemirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "shell.h"

/*  builtin functions   */
int	builtin_cd(t_ms_data *data);
int	builtin_echo(t_ms_data *data);
int	builtin_env(t_ms_data *data);
int	builtin_exit(t_ms_data *data);
int	builtin_export(t_ms_data *data);
int	builtin_pwd(t_ms_data *data);
int	builtin_unset(t_ms_data *data);

#endif
