#include <stdio.h>
#include <unistd.h>
#include "signals.h"
#include <signal.h>
#include <errno.h>
#include <bits/sigaction.h>
#include <asm-generic/signal-defs.h>

volatile sig_atomic_t g_signo = 0;

void init_signals()
{
    struct sigaction signal_action;

    signal_action.sa_handler = sigint_handler;
    sigemptyset(&signal_action.sa_mask);
    signal_action.sa_flags = SA_RESTART;

    if (sigaction(SIGINT, &signal_action, NULL) == -1)
    {
        perror("Error: cannot handle SIGINT");
    }

    signal_action.sa_handler = sigquit_handler;
    if (sigaction(SIGQUIT, &signal_action, NULL) == -1)
    {
        perror("Error: cannot handle SIGQUIT");
    }
}

