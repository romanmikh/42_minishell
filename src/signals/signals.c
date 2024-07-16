/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmdemirk <dmdemirk@student.42london.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 11:22:46 by dmdemirk          #+#    #+#             */
/*   Updated: 2024/07/16 17:17:52 by dmdemirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include "signals.h"
#include <signal.h>
#include <errno.h>
#include <bits/sigaction.h>
#include <asm-generic/signal-defs.h>
#include <readline/readline.h>
#include <readline/history.h>

volatile sig_atomic_t	g_signo = 0;

void	init_signals(void);
void	sigint_handler(int signo);
void	sigquit_handler(int signo);

/*
• Handle ctrl-C, ctrl-D and ctrl-\ which should behave like in bash.
• In interactive mode:
	◦ ctrl-C displays a new prompt on a new line.
	◦ ctrl-D exits the shell.
	◦ ctrl-\ does nothing.
https://github.com/zstenger93/minishell/blob/master/src/signals/signals.c#L33

*/

void	init_signals(void)
{
	struct sigaction	signal_action;

	signal_action.sa_flags = SA_RESTART;
	sigemptyset(&signal_action.sa_mask);
	signal_action.sa_handler = sigint_handler; // ^C signal
	if (sigaction(SIGINT, &signal_action, NULL) == -1)
		ft_perror("Error: SIGINT");
	signal_action.sa_handler = sigquit_handler; // ^\ signal
	if (sigaction(SIGQUIT, &signal_action, NULL) == -1)
		ft_perror("Error: SIGQUIT");
}

void	sigint_handler(int signo)
{
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_signo = signo;
}

void	sigquit_handler(int signo)
{
	(void)signo;
	write(STDOUT_FILENO, "", 0);
    rl_on_new_line();
	rl_replace_line("", 0);
    rl_redisplay();
    g_signo = SIGQUIT;
}
