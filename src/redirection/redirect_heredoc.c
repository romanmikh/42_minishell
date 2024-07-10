#include "shell.h"
#include "tokens.h"
#include "redirection.h"
#include "execute.h"
#include <fcntl.h>

/**
- @brief This function handle "<<" heredoc functionality
- 
- @param node current node in the AST
- @param data minishell data structure
- @return status:
            0: success
            1: error
 */

int redirect_here_doc(t_ast *node, t_minishell_data *data)
{
    char   *line;
    char   *eof;
    int    file_fd;
    pid_t  pid;

    line = NULL;

    if (node->right->args[0] == NULL)
        return (1);
    eof = ft_strdup(node->right->args[0]);
    file_fd = open("/tmp/heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (file_fd < 0)
    {
        free(eof);
        return (1);
    }
    line = readline("> ");
    while (line && (ft_strcmp(line, eof) != 0))
    {
        write(data->std_out, line, ft_strlen(line));
        write(data->std_out, "\n", 1);
        free(line);
        line = readline("> ");
    }
    free(line);
    free(eof);
    close(file_fd);

    file_fd = open("/tmp/heredoc", O_RDONLY);
    data->std_in = file_fd;
    if (file_fd < 0)
        return (1);
    pid = fork();
    if (pid == -1)
        ft_perror("fork");
    if (pid == 0)
    {
        close_fds(data->std_in, data->std_out);
        execute_ast(node->left, data);
        exit(1);
    }
    return (0);
}
