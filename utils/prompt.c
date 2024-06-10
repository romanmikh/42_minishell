/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmikhayl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 13:58:23 by rmikhayl          #+#    #+#             */
/*   Updated: 2024/06/10 16:44:47 by dmdemirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include "env.h"

/*
todo: 
extract and print only after LOGNAME

!wrong example:
🌴 dmdemirk@maxishell:~/home/dmdemirk/Documents/minishell>

correct example:
🌴 dmdemirk@maxishell:~/Documents/minishell>
 */

char	*generate_prompt(t_minishell_data *data)
{
	char	*prompt;
	size_t	prompt_len;

	prompt_len = strlen("🌴\e[1m @maxishell:~> \e[m") + \
					strlen(get_env(data->envp, "LOGNAME")) + \
					ft_strlen(get_env(data->envp, "PWD")) + \
					1;
	prompt = (char *)malloc(prompt_len);
	if (!prompt)
		exit(EXIT_FAILURE);
	ft_strcpy(prompt, "🌴\e[1m ");
	ft_strcat(prompt, get_env(data->envp, "LOGNAME"));
	ft_strcat(prompt, "@maxishell:~");
	ft_strcat(prompt, get_env(data->envp, "PWD"));
	ft_strcat(prompt, "> \e[m");
	return (prompt);
}
