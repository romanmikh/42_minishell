/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmdemirk <dmdemirk@student.42london.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 14:07:19 by dmdemirk          #+#    #+#             */
/*   Updated: 2024/07/17 14:32:30 by dmdemirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include <signal.h>
# include "shell.h"

/*      gloval variable     */
extern volatile sig_atomic_t	g_signo;

/*      signals     */
void	init_signals(void);

/*		utils		*/
void	signal_handler(int signo);
void	sigint_handler(int signo);
void	sigquit_handler(int signo);

int		ft_perror(char *str);
#endif
