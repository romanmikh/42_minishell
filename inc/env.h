/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmdemirk <dmdemirk@student.42london.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 17:20:26 by dmdemirk          #+#    #+#             */
/*   Updated: 2024/06/10 16:45:25 by dmdemirk         ###   ########.fr       */
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

/*	env		*/
void	init_env(t_env **data_envp, char **envp);
void	add_env_node(t_env **data_envp, char *line);
char	*get_env(t_env *envp, const char *key);
void	set_env(t_env **env, const char *key, const char *value);
int		unset_env(t_env **env, const char *name);

/*	utils	*/
char	**env_to_array(t_env *envp);
char	*ft_strcdup(const char *s, int c);
void	free_env(t_env *envp);

/*	shell variables	*/
int handle_add_set_shell_variable(t_env *shell_var, char *line);
int handle_get_shell_variable(t_env *shell_var, const char *key);

/*	shell variables utils	*/
void	set_shell_var(t_env **shell_var, const char *key, const char *value);
void    add_shell_var_node(t_env **shell_var, const char *line);
char	*get_shell_variable(t_env *shell_var, const char *key);

#endif
