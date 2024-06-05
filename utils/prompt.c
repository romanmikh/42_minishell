/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmikhayl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 13:58:23 by rmikhayl          #+#    #+#             */
/*   Updated: 2024/06/05 14:22:25 by rmikhayl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"

char	*generate_prompt(void)
{
	char	*prompt;
	size_t	prompt_len;

	prompt_len = strlen("🌴\e[1m @maxishell:~> \e[m") + \
			strlen(getenv("LOGNAME")) + \
			ft_strlen(getenv("PWD")) + \
			1;
	prompt = (char *)malloc(prompt_len);
	if (!prompt)
		exit(EXIT_FAILURE);
	ft_strcpy(prompt, "🌴\e[1m ");
	ft_strcat(prompt, getenv("LOGNAME"));
	ft_strcat(prompt, "@maxishell:~");
	ft_strcat(prompt, getenv("PWD"));
	ft_strcat(prompt, "> \e[m");
	return (prompt);
}
