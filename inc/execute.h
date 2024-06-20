/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmdemirk <dmdemirk@student.42london.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:34:42 by dmdemirk          #+#    #+#             */
/*   Updated: 2024/06/04 18:06:52 by dmdemirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "shell.h"
# include "tokens.h"

/*	execute	*/
int		execute(t_minishell_data *data);
int execute_ast(t_ast *tree, t_minishell_data *data);
int	execution_manager(t_ast *node, t_minishell_data *data);

/*	utils	*/
char	*ft_find_path(char *cmd, t_env *envp);
void	ft_free_2d_arr(char **arr);

#endif
