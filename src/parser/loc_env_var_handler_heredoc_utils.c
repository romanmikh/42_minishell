/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loc_env_var_handler_heredoc_utils.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmikhayl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 01:04:20 by rmikhayl          #+#    #+#             */
/*   Updated: 2024/09/10 01:04:22 by rmikhayl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "tokens.h"
#include "redirection.h"
#include "execute.h"
#include <fcntl.h>
#include <sys/wait.h>
#include "signals.h"

char	*token_adj(char *arg)
{
	char	*ptr;
	char	*new_arg;

	if (*arg == '\"')
	{
		ptr = arg + 1;
		while (*ptr && *ptr != '\"')
		{
			if (!ft_isdigit(*ptr))
				return (ft_strdup(arg));
			ptr++;
		}
		if (*ptr == '\0')
		{
			new_arg = malloc(ft_strlen(arg) + 2);
			if (!new_arg)
				return (NULL);
			ft_strcpy(new_arg, arg);
			ft_strcat(new_arg, "\"");
			return (new_arg);
		}
		if (*ptr == '\"' && *(ptr + 1) == '\0')
			return (ft_strdup(arg));
	}
	return (ft_strdup(arg));
}
