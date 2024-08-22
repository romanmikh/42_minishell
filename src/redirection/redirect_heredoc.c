/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmdemirk <dmdemirk@student.42london.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 14:32:29 by dmdemirk          #+#    #+#             */
/*   Updated: 2024/07/11 16:00:30 by dmdemirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "tokens.h"
#include "redirection.h"
#include "execute.h"
#include <fcntl.h>
#include <sys/wait.h>

int			redirect_here_doc(t_ast *node, t_ms_data *data);
static int	open_tmp_file(const char *type);
static void	execute_child(t_ast *node, t_ms_data *data, int *file_fd);

/**
  - @brief This function handle "<<" heredoc functionality
  - 
  - @param node current node in the AST
  - @param data minishell data structure
  - @return status:
  - 0: success
  - 1: error
 */

int	redirect_here_doc(t_ast *node, t_ms_data *data)
{
	char	*line;
	char	*eof;
	int		file_fd;

	line = NULL;
	if (node->right->args[0] == NULL)
		return (1);
	file_fd = open_tmp_file("w");
	eof = ft_strdup(node->right->args[0]);
	line = readline("> ");
	while (line && (ft_strcmp(line, eof) != 0))
	{
		write(file_fd, line, ft_strlen(line));
		write(file_fd, "\n", 1);
		free(line);
		line = readline("> ");
	}
	free(line);
	free(eof);
	close(file_fd);
	file_fd = open_tmp_file("r");
	execute_child(node->left, data, &file_fd);
	unlink("/tmp/heredoc");
	return (0);
}

static int	open_tmp_file(const char *type)
{
	int	file_fd;	

	file_fd = -1;
	if (ft_strcmp(type, "w") == 0)
		file_fd = open("/tmp/heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (ft_strcmp(type, "r") == 0)
		file_fd = open("/tmp/heredoc", O_RDONLY);
	if (file_fd < 0)
		ft_perror("open");
	return (file_fd);
}

static void	execute_child(t_ast *node, t_ms_data *data, int *file_fd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		ft_perror("fork");
	if (pid == 0)
	{
		data->std_in = dup(*file_fd);
		execute_ast(node, data);
		exit(0);
	}
	close(*file_fd);
	waitpid(pid, &data->exit_status, 0);
}
