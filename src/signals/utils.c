/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmdemirk <dmdemirk@student.42london.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 11:22:53 by dmdemirk          #+#    #+#             */
/*   Updated: 2024/07/17 17:05:23 by dmdemirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include "signals.h"

void	signal_handler(int signo)
{
	if (signo == SIGINT)
		sigint_handler(signo);
	else if (signo == SIGQUIT)
		sigquit_handler(signo);
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
	g_signo = signo;
}
