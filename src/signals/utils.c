#include <signal.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft.h"

void sigint_handler(int signo)
{
    const char *msg;
	
	(void)signo;
	msg = "SIGINT received\n";
    write(STDOUT_FILENO, msg, ft_strlen(msg));
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}
