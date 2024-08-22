/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmdemirk <dmdemirk@student.42london.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 11:02:59 by dmdemirk          #+#    #+#             */
/*   Updated: 2024/06/26 14:39:51 by dmdemirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPE_H
# define PIPE_H

# include "shell.h"
# include "tokens.h"

# define WAIT_NEXT_COMMAND 1

/*  pipe    */
int	builtin_pipe(t_ast *node, t_ms_data *data);

#endif
