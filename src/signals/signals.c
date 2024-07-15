#include <signal.h>
#include <stdio.h>
#include "signals.h"

void init_signals()
{
	struct sigaction sa;

	sa.sa_handler = sigint_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;

    if(sigaction(SIGINT, &sa, NULL) == -1)
    {
        perror("Error: cannot handle SIGINT");
    }
    signal(SIGQUIT, SIG_IGN);
}