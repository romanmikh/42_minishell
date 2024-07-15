#ifndef SIGNALS_H
# define SIGNALS_H

#include <signal.h>
#include "shell.h"

/*      gloval variable     */
extern volatile sig_atomic_t g_signo;

/*      signals     */
void init_signals();

/*      utils       */
void signals_handler(int signo, t_minishell_data *data);
void sigint_handler(int signo);
void sigquit_handler(int signo);

#endif