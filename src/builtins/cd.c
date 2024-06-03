#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libft.h"

int	cd(char *path)
{
	if (path == NULL)
		write(2, "cd: missing argument\n", ft_strlen("cd: missing argument\n"));	
	if (chdir(path) != 0)
		perror("cd");	
	return (0);
}
