#include "tokens.h"
#include "shell.h"
#include "redirection.h"
#include "execute.h"
#include "pipe.h"

pid_t	execute_redirect(t_ast *node, t_minishell_data *data, \
			int fd[2], int direction);

/**
- @brief redirect out in the context of executing AST
-        looking similar to the pipe function
- 
- @param node current node in the AST
- @param data minishell data structure
- @return int status:
- 				- 0: success
- 				- 1: error
 */

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

/**
- @brief execute child process in the redirection context
- 
- @param node current node in the AST
- @param data minishell data structure
- @param fd file descriptors
- @param direction redirection if 0 - node_left, if 1 - node_right
- @return pid_t the process id
 */

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
