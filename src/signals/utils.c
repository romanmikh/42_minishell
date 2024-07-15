#include <signal.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft.h"
#include "shell.h"
#include "signals.h"

void signals_handler(int signo, t_minishell_data *data);
void sigint_handler(int signo);
void sigquit_handler(int signo);

void signals_handler(int signo, t_minishell_data *data)
{
    (void)data; // Чтобы избежать предупреждения о неиспользуемой переменной
    if (g_signo)
    {
        if (signo == SIGINT)
        {
            write(STDOUT_FILENO, "\n", 1);
            rl_on_new_line();
            rl_replace_line("", 0);
            rl_redisplay();
        }
        else if (signo == SIGQUIT)
        {
            // Обработка SIGQUIT, если необходимо
        }
        
    }
}

void sigint_handler(int signo)
{
    g_signo = signo;
}

void    sigquit_handler(int signo)
{
    g_signo = signo;
}
