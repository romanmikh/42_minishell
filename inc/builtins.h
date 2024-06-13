/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmdemirk <dmdemirk@student.42london.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:34:46 by dmdemirk          #+#    #+#             */
/*   Updated: 2024/06/04 12:18:43 by dmdemirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "shell.h"

/*  builtin functions   */
int	builtin_cd(t_minishell_data *data);
int	builtin_echo(t_minishell_data *data);
int	builtin_env(t_minishell_data *data);
int	builtin_exit(t_minishell_data *data);
int builtin_export(t_minishell_data *data);
// int	pwd(char **argv);
// int	unset(char **argv);

#endif
