/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmdemirk <dmdemirk@student.42london.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 17:20:26 by dmdemirk          #+#    #+#             */
/*   Updated: 2024/06/07 17:25:44 by dmdemirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}				t_env;

/*	utils	*/
void	init_env(t_env **data_envp, char **envp);
char    *ft_strcdup(const char *s, int c);
void	add_env_node(t_env **data_envp, char *line);

/*	env		*/
char *get_env_value(t_env *envp, char *key);
char **env_to_array(t_env *envp);

#endif
