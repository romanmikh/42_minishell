#include "builtins.h"

int	cd(char **argv);


int	execute(char **args)
{
	int	i;
	char	*builtin_functions[] = {
		"cd",
		"echo",
		"env",
		"exit",
		"export",
		"pwd",
		"unset"
	};
	
	int	(*builtin_functions[])(char **) = {
		&cd, 
		&echo,
		&env,
		&exit,
		&export,
		&pwd,
		&unset
	};
	i = -1;
	if (args[0] == NULL)
		return(EXIT_FAILURE);
	while (++i < sizeof(builtin_functions) / sizeof(char *))
	{
		if (ft_strcmp(args[0], builtin_functions[i]) == 0)
			return ((*builtin_functions[i](args));	
	}
	return (new_process(args));
}
