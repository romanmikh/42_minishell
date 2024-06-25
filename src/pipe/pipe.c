/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmdemirk <dmdemirk@student.42london.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 11:04:39 by dmdemirk          #+#    #+#             */
/*   Updated: 2024/06/17 11:17:02 by dmdemirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include <unistd.h>
#include "libft.h"
#include "execute.h"
#include <stdio.h>
#include <sys/wait.h>

int	ft_perror(char *str);
void	builtin_pipe(t_ast *node, t_minishell_data *data);
void close_fds(int fds[2]);
int execute_child(t_ast *node, t_minishell_data *data, int fd[2], int direction);

void	builtin_pipe(t_ast *node, t_minishell_data *data)
{
   	int fd[2];
    pid_t pid_1, pid_2;

    if (pipe(fd) == -1)
        ft_perror("pipe");
    pid_1 = execute_child(node->left, data, fd, 0);
    pid_2 = execute_child(node->right, data, fd, 1);
    close_fds(fd); 
    if (pid_1 > 0) 
        waitpid(pid_1, NULL, 0);
    if (pid_2 > 0)
        waitpid(pid_2, NULL, 0);
}

int	execute_child(t_ast *node, t_minishell_data *data, int fd[2], int direction) 
{
    pid_t pid;
    
    pid = fork();
    if (pid == -1)
        ft_perror("fork");
    if (pid == 0) 
    {
        if (direction == 0)
            dup2(fd[1], STDOUT_FILENO);
        else
            dup2(fd[0], STDIN_FILENO);
        close_fds(fd);
        execution_manager(node, data);
        exit(EXIT_SUCCESS);
    }
    return pid;
}