#include "libft.h"

int echo(int argc, char **argv)
{
	int	newline;
	int	i;

	newline = 1;
	if (argc > 1 && ft_strcmp(argv[1], "-n") == 0)
	{
		newline = 0;
		argv++;
		argc--;
	}
	i = -1;
	while (++i < argc)
		write(1, argv[i], ft_strlen(argv[i]));
	if (newline)
		write(1, "\n", 1);	
	return (0);
}
