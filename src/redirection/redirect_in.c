#include "tokens.h"
#include "shell.h"
#include "redirection.h"
#include "execute.h"
#include <string.h>

/*
	! FIX
	wc < input.txt - work fine
	wc -l < input.txt - not work (:bad address error)
*/

/**
- @brief redirection input in context of executing AST
- 
- @param node current node in the AST
- @param data minishell structure data
- @return int return status:
- 				- 0: success
- 				- 1: error
 */

int	 redirect_in(t_ast *node, t_minishell_data *data)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (1);
	if (pid == 0)
	{
		data->temp_fd = open_file(node->right, "<");
		if (data->temp_fd == -1)
			return (1);
		execute_ast(node->left, data);
		exit(0);
	}
	waitpid(pid, &data->exit_status, 0);
	return (0);
}