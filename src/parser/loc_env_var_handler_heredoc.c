/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loc_env_var_handler_heredoc.c                      :+:      :+:    :+:   */
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
#include "signals.h"

static char	*assemble_result(char **tokens, size_t result_len);
char		*token_adj(char *arg);
char		*finalize_token(char *tmp_token, char *orig_token);
size_t		process_single_token(char **token, t_ms_data *data);
size_t		process_tokens(char **tokens, t_ms_data *data);

char	*process_and_reassemble(char *line, t_ms_data *data)
{
	char	**tokens;
	size_t	result_len;
	char	*result;

	tokens = ft_split(line, ' ');
	free(line);
	if (!tokens)
		return (NULL);
	result_len = process_tokens(tokens, data);
	result = assemble_result(tokens, result_len);
	ft_free_2d_arr(tokens);
	return (result);
}

size_t	process_tokens(char **tokens, t_ms_data *data)
{
	int		i;
	size_t	result_len;

	result_len = 0;
	i = 0;
	while (tokens[i])
	{
		result_len += process_single_token(&tokens[i], data);
		i++;
	}
	return (result_len);
}

size_t	process_single_token(char **token, t_ms_data *data)
{
	char	*orig_token;
	char	*tmp_token;
	char	*new_token;
	size_t	new_len;

	orig_token = *token;
	tmp_token = expand_variable(token, data);
	new_token = finalize_token(tmp_token, orig_token);
	*token = new_token;
	free(orig_token);
	new_len = ft_strlen(new_token) + 1;
	return (new_len);
}

char	*finalize_token(char *tmp_token, char *orig_token)
{
	char	*processed_token;
	char	*new_token;

	if (tmp_token)
	{
		processed_token = token_adj(tmp_token);
		if (processed_token != tmp_token)
		{
			new_token = ft_strdup(processed_token);
			free(tmp_token);
		}
		else
			new_token = tmp_token;
		free(processed_token);
	}
	else
		new_token = ft_strdup(orig_token);
	return (new_token);
}

static char	*assemble_result(char **tokens, size_t result_len)
{
	char	*result;
	int		i;

	result = malloc(result_len + 1);
	if (!result)
		return (NULL);
	*result = '\0';
	i = 0;
	while (tokens[i])
	{
		ft_strcat(result, tokens[i]);
		if (tokens[i + 1])
			ft_strcat(result, " ");
		i++;
	}
	return (result);
}
