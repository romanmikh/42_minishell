/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmdemirk <dmdemirk@student.42london.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 13:59:59 by dmdemirk          #+#    #+#             */
/*   Updated: 2024/09/09 12:32:04 by dmdemirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include "libft.h"
#include "exit_status.h"

void	signal_reset_prompt(int signo, siginfo_t *info, void *ucontext);
void	set_signals_interactive(t_ms_data *data);
void	signal_print_newline(int signal);
void	sigquit_ignore(void);
void	set_signals_noninteractive(void);

void	signal_print_newline(int signal)
{
	(void)signal;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
}

void	sigquit_ignore(void)
{
	struct sigaction	a;

	sigemptyset(&a.sa_mask);
	a.sa_flags = 0;
	a.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &a, NULL);
}

void	set_signals_interactive(t_ms_data *data)
{
	t_signal_context	*context;
	struct sigaction	sa;

	context = get_context(data);
	if (!context)
		return ;
	sa.sa_sigaction = signal_reset_prompt;
	sa.sa_flags = SA_RESTART | SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
}

void	signal_reset_prompt(int signo, siginfo_t *info, void *ucontext)
{
	t_signal_context	*context;

	(void)signo;
	(void)info;
	(void)ucontext;
	context = get_context(NULL);
	if (!rl_line_buffer || rl_line_buffer[0] == '\0')
	{
		if (context && context->data_cxt)
		{
			ft_printf("\nexit\n");
			handle_exit(context->data_cxt, 0);
		}
	}
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	set_signals_noninteractive(void)
{
	struct sigaction	sa;

	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGQUIT, &sa, NULL);
}
