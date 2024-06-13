#include "shell.h"
#include <unistd.h>
#include "libft.h"
#include "execute.h"
#include <stdio.h>

void	builtin_pipe(t_minishell_data *data)
{
	pid_t	pid;
	int		fd[2];

	pipe(fd);
	pid = fork();
	if (pid == -1)
	{
		perror ("Error");
		exit (EXIT_FAILURE);
	}
	if (pid == 0)
	{
		close(fd[0]);
		if (dup2(fd[1], STDOUT_FILENO) == -1)
		{
			perror ("Error");
			exit (EXIT_FAILURE);
		}
		close(fd[1]);
		execute(data);
	}
	else
	{
		close(fd[1]);
		if (dup2(fd[0], STDIN_FILENO) == -1)
		{
			perror ("Error");
			exit (EXIT_FAILURE);
		}
		close(fd[0]);
		waitpid(pid, NULL, 0);
	}
}