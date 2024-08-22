/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmdemirk <dmdemirk@student.42london.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 16:48:39 by dmdemirk          #+#    #+#             */
/*   Updated: 2024/06/17 11:04:00 by dmdemirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_H
# define TEST_H

# include "shell.h"

/*  env     */
void	env_tests(t_ms_data *data, char **envp);

/*  pipe    */
void	pipe_tests(t_ms_data *data);

#endif
