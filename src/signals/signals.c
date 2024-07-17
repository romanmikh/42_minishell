/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmdemirk <dmdemirk@student.42london.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 13:59:59 by dmdemirk          #+#    #+#             */
/*   Updated: 2024/07/17 14:33:29 by dmdemirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <bits/sigaction.h>
#include <asm-generic/signal-defs.h>
#include "signals.h"

volatile sig_atomic_t	g_signo = 0;

void	init_signals(void)
{
	struct sigaction	signal_action;

	signal_action.sa_handler = signal_handler;
	sigemptyset(&signal_action.sa_mask);
	signal_action.sa_flags = SA_RESTART;
	sigaction(SIGINT, &signal_action, NULL);
	sigaction(SIGQUIT, &signal_action, NULL);
}
