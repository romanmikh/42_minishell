/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rocky <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 14:56:25 by rocky             #+#    #+#             */
/*   Updated: 2024/06/11 14:58:49 by rocky            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include "env.h"

void	free_args(char **args)
{
	int	i;

	i = 0;
	if (args)
	{
		while (args[i] != NULL)
			free(args[i++]);
		free(args);
	}
}

void	free_env_list(t_env *env)
{
	t_env	*temp;

	while (env)
	{
		free(env->key);
		free(env->value);
		temp = env;
		env = env->next;
		free(temp);
	}
}

void	free_minishell_data(t_minishell_data *data)
{
	if (data)
	{
		free_args(data->args);
		free_env_list(data->envp);
		free_env_list(data->local_env);
		free(data->current_dir);
		free(data);
	}
}

void	cleanup(char *line, t_token *tokens, char *prompt)
{
	free(line);
	(void)tokens;
	(void)prompt;
	//free_all_tokens(tokens);
	//free(prompt);
}
