/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmdemirk <dmdemirk@student.42london.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:34:42 by dmdemirk          #+#    #+#             */
/*   Updated: 2024/09/10 13:18:54 by rmikhayl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "shell.h"
# include "tokens.h"
# include "env.h"

/*	execute	*/
int	execute_ast(t_ast *node, t_ms_data *data);
int	execute(t_ms_data *data);

/*	utils	*/
char	*ft_find_path(char *cmd, t_env *envp);
void	ft_free_2d_arr(char **arr);
int	ft_perror(char *str);
void	close_fds(int in, int out);
void	handle_io_fd(t_ms_data *data);
void	handle_std_io(int *std_io, int std_fileno);

/*  shell variable execution */
int	handle_shell_variable(t_ast *node, t_ms_data *data);
int	handle_get_shell_variable(t_ms_data *data, const char *key);
void	shell_variable_update(t_ms_data *data, int status);

#endif
