/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmdemirk <dmdemirk@student.42london.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 14:33:02 by dmdemirk          #+#    #+#             */
/*   Updated: 2024/09/09 13:49:49 by dmdemirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include <fcntl.h>
#include "libft.h"
#include "tokens.h"
#include "exit_status.h"

int			open_file(t_ast *node, char *direction);
int			open_tmp_file(const char *type);

/**
  - @brief open file in the context of redirection
  -       "<" - read
  -       ">" - write
  -       ">>" - append
  -       "tty" - open /dev/tty
  - 
  - @param node current node in the AST
  - @param direction type of redirection 
  - @return int file descriptor
 */

int	open_file(t_ast *node, char *direction)
{
	int	fd;

	if ((ft_strcmp(direction, "<") == 0) || (ft_strcmp(direction, "read") == 0))
		fd = open(node->args[0], O_RDONLY);
	else if (ft_strcmp(direction, ">") == 0)
		fd = open(node->args[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if ((ft_strcmp(direction, ">>") == 0) \
			|| (ft_strcmp(direction, "temp") == 0))
		fd = open(node->args[0], O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (ft_strcmp(direction, "tty") == 0)
		fd = open("/dev/tty", O_RDWR);
	else
		fd = -1;
	return (fd);
}

int	open_tmp_file(const char *type)
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
