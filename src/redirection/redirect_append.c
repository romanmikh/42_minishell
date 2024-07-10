#include "shell.h"
#include "tokens.h"
#include "redirection.h"
#include "execute.h"

/**
- @brief redirect append ">>" to the end of the file output
- 
- @param node current node in the AST
- @param data minishell data structure
- @return status:
            0: success
            1: error
 */

int redirect_append(t_ast *node, t_minishell_data *data)
{
    pid_t pid;
    int status;

    pid = fork();
    if (pid == -1)
        return (1);
    if (pid == 0)
    {
        data->std_out = open_file(node->right, ">>");
        if (data->std_out == -1)
            return (1);
        execute_ast(node->left, data);
        exit(0);
    }
    waitpid(pid, &status, 0);
    return (WEXITSTATUS(status));
}