#include "tokens.h"
#include "shell.h"
#include "redirection.h"
#include "execute.h"
#include "pipe.h"

pid_t	execute_redirect(t_ast *node, t_minishell_data *data, \
			int fd[2], int direction);

int redirect_out(t_ast *node, t_minishell_data *data)
{
    	int	fd[2];
	pid_t	pid_1;
	pid_t	pid_2;
	int	status;

	if (pipe(fd) == -1)
		ft_perror("pipe");
	pid_1 = execute_redirect(node->left, data, fd, 0);
	pid_2 = execute_redirect(node->right, data, fd, 1);
	close_fds(fd);
	waitpid(pid_1, &status, 0);
    	waitpid(pid_2, &status, 0);
	return (WEXITSTATUS(status));
}

pid_t execute_redirect(t_ast *node, t_minishell_data *data, int fd[2], int direction)
{
    pid_t pid;

    pid = fork();
    if (pid == -1)
        ft_perror("fork");  
    if (pid == 0)
    {
        if (direction == 0)
        {
            dup2(fd[1], STDIN_FILENO);
            close_fds(fd);
            execute_ast(node, data);
            exit(EXIT_SUCCESS);
        }
        else if (direction == 1)
        {
            fd[0] = open_file(node, ">");
            dup2(fd[0], STDOUT_FILENO);
            close_fds(fd);
        }
    }
    return (pid);
}
