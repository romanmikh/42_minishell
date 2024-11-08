/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rocky <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 13:43:47 by rocky             #+#    #+#             */
/*   Updated: 2024/09/06 13:43:49 by rocky            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include "libft.h"
#include <sys/wait.h>

// Pulls ms_data into sigint handler, bypassing need of second global variable
t_signal_context	*get_context(t_ms_data *data)
{
	static t_signal_context	*context = NULL;

	if (data != NULL)
	{
		if (!context)
		{
			context = malloc(sizeof(t_signal_context));
			if (!context)
				return (NULL);
		}
		context->data_cxt = data;
	}
	return (context);
}

void	handle_sigint_heredoc(int signo)
{
	(void)signo;
	g_heredoc_interrupted = 1;
}

int	is_external_command_running(void)
{
	pid_t	child_pid;

	child_pid = waitpid(-1, NULL, WNOHANG);
	if (child_pid == 0)
		return (1);
	else
		return (0);
}
