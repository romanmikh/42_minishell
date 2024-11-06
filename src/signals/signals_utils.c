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

// void	handle_sigint_heredoc(int signo)
// {
// 	(void)signo;
// 	g_heredoc_interrupted = 1;
// 	write(1, "\n", 1);
// 	handle_exit
// 	rl_replace_line("", 0);
// 	rl_redisplay();

// }


// #include "signals.h"
// #include <readline/readline.h>
// #include <readline/history.h>
// #include <unistd.h>
// #include "libft.h"
#include "exit_status.h"

void handle_sigint_heredoc(int signo)
{
    (void)signo;
    
    // Retrieve context to access data for handle_exit
    t_signal_context *context = get_context(NULL);
    
    if (context && context->data_cxt)
    {
        handle_exit(context->data_cxt, 0);
    }

    g_heredoc_interrupted = 1;
    write(1, "\n", 1);
    rl_replace_line("", 0);
    rl_redisplay();
}
