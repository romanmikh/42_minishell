/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmdemirk <dmdemirk@student.42london.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 13:59:59 by dmdemirk          #+#    #+#             */
/*   Updated: 2024/07/18 16:42:07 by dmdemirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include "libft.h"

void	signal_reset_prompt(int signo);
void	set_signals_interactive(void);
void	signal_print_newline(int signal);
void	sigquit_ignore(void);
void	set_signals_noninteractive(void);

void	signal_reset_prompt(int signo)
{
	(void)signo;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	set_signals_interactive(void)
{
	struct sigaction	a;

	sigquit_ignore();
	sigemptyset(&a.sa_mask);
	a.sa_handler = *signal_reset_prompt;
	sigaction(SIGINT, &a, NULL);
}

void	signal_print_newline(int signal)
{
	(void)signal;
	rl_on_new_line();
}

void	sigquit_ignore(void)
{
	struct sigaction	a;

	sigemptyset(&a.sa_mask);
	a.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &a, NULL);
}

void	set_signals_noninteractive(void)
{
	struct sigaction	a;

	sigemptyset(&a.sa_mask);
	a.sa_handler = &signal_print_newline;
	sigaction(SIGINT, &a, NULL);
	sigaction(SIGQUIT, &a, NULL);
}
