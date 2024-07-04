#include "shell.h"
#include <fcntl.h>
#include "libft.h"
#include "tokens.h"

int open_file(t_ast *node, char *direction);
// void redirect(t_minishell_data *data, int fd, char *direction);
// int execute_redirection(t_ast *node, t_minishell_data *data);

int open_file(t_ast *node, char *direction)
{
    int fd;
    
    if (ft_strcmp(direction, ">") == 0)
        fd = open(node->args[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    else if (ft_strcmp(direction, ">>") == 0)
        fd = open(node->args[0], O_WRONLY | O_CREAT | O_APPEND, 0644);
    else if (ft_strcmp(direction, "<") == 0)
        fd = open(node->args[0], O_RDONLY);
    else if (ft_strcmp(direction, "tty") == 0)
        fd = open("/dev/tty", O_RDWR);
    else
        fd = -1;
    return (fd);
}

// void redirect(t_minishell_data *data, int fd, char *direction)
// {
//     if (ft_strcmp(direction, ">") == 0 || ft_strcmp(direction, ">>") == 0)
//         dup2(fd, STDOUT_FILENO);
//     else if (ft_strcmp(direction, "<") == 0)
//         dup2(fd, STDIN_FILENO);
//     close(fd);
// }

// int execute_redirection(t_ast *node, t_minishell_data *data)
// {
//     int fd;
//     size_t i;

//     i = 0;
//     while (node->args[i] != NULL)
//     {
//         if (ft_strcmp(node->args[i], ">") == 0 || ft_strcmp(node->args[i], ">>") == 0 || ft_strcmp(node->args[i], "<") == 0)
//         {
//             fd = open(data, node->args[i]);
//             if (fd == -1)
//                 return (1);
//             redirect(data, fd, node->args[i]);
//         }
//         i++;
//     }
//     return (0);
// }
