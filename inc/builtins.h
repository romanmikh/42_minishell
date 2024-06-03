/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmdemirk <dmdemirk@student.42london.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:34:46 by dmdemirk          #+#    #+#             */
/*   Updated: 2024/06/03 16:34:47 by dmdemirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

/*  builtin functions   */
int	builtin_cd(char **args);
int	builtin_echo(char **argv);
int	builtin_env(char **argv);
int	builtin_exit(char **argv);
// int	export(char **argv);
// int	pwd(char **argv);
// int	unset(char **argv);

#endif
