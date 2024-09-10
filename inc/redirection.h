/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmdemirk <dmdemirk@student.42london.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 14:59:47 by dmdemirk          #+#    #+#             */
/*   Updated: 2024/09/09 13:49:13 by dmdemirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTION_H
# define REDIRECTION_H

# include "shell.h"
# include "tokens.h"

/*  redirect_in */
int		redirect_in(t_ast *node, t_ms_data *data);
int		redirect_out(t_ast *node, t_ms_data *data);
int		redirect_append(t_ast *node, t_ms_data *data);
int		redirect_here_doc(t_ast *node, t_ms_data *data);
char	*process_and_reassemble(char *line, t_ms_data *data);

/*  utils   */
int		open_file(t_ast *node, char *direction);
int		open_tmp_file(const char *type);

#endif
