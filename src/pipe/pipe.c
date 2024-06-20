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

void	ft_perror(char *str);
void	builtin_pipe(t_ast *node, t_minishell_data *data);

void	builtin_pipe(t_ast *node, t_minishell_data *data)
{
    pid_t	pid_1, pid_2;
    int		fd[2];

    if (pipe(fd) == -1)
        ft_perror("pipe");
    pid_1 = fork();
    if (pid_1 == -1)
        ft_perror("fork");
    if (pid_1 == 0)
    {
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);
        execution_manager(node->left, data);
        exit(EXIT_FAILURE);
    }
    pid_2 = fork();
    if (pid_2 == -1)
        ft_perror("fork");
    if (pid_2 == 0)
    {
        close(fd[1]);
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]);
        execution_manager(node->right, data);
        exit(EXIT_FAILURE);
    }
    close(fd[0]);
    close(fd[1]);
    waitpid(pid_1, &data->exit_status, 0);
    waitpid(pid_2, &data->exit_status, 0);
}

void	ft_perror(char *str)
{
	perror (str);
	exit (EXIT_FAILURE);
}
