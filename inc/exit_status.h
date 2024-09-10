/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmdemirk <dmdemirk@student.42london.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 12:29:24 by dmdemirk          #+#    #+#             */
/*   Updated: 2024/09/09 13:20:14 by dmdemirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXIT_STATUS_H
# define EXIT_STATUS_H

# define EXIT_SUCCESS   0
# define EXIT_FAILURE   1
# define EXIT_MISUSE    2

# define IS_DIRECTORY 256
# define NUMERIC_REQUIRED 257
# define TOO_MANY_ARGS 258
# define UNKNOWN_COMMAND 259
# define INVALID_ARGUMENT 260
# define PERMISSION_DENIED 261
# define ERROR_EXIT 262
# define NOT_VALID_IDENTIFIER 263
# define INVALID_OPTION 264

# include "shell.h"
# include <errno.h>

/*  exit status  */
void	exit_status_handler(t_ms_data *data, int status_code, char *err_arg);
void	set_exit_status(int *exit_status, int status_code);

/*  exit_status_utils    */
int		ft_perror(char *str);
int		ft_isnumber(char *str);
void	free_shell_var_list(t_env *shell_var);

#endif
