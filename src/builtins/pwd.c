
#include "shell.h"
#include <unistd.h>
#include "libft.h"
#include <stdio.h>

/*
    Functionality:
        - Print the current working directory
*/

int builtin_pwd(t_minishell_data *data)
{
    char	cwd[4096];

    (void)data;
    if (getcwd(cwd, sizeof(cwd)) != NULL)
        ft_putendl_fd(cwd, STDOUT_FILENO);
    else
   	{
		ft_putstr_fd("bash: cd: ", 2);
		perror("cwd");
		return (1);
	}
    return (0);
}