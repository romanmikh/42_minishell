/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmdemirk <dmdemirk@student.42london.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 18:52:00 by dmdemirk          #+#    #+#             */
/*   Updated: 2024/07/11 18:52:07 by dmdemirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"

t_ast	*parse_tokens(t_token **tokens, t_ms_data *data);

t_ast	*parse_tokens(t_token **tokens, t_ms_data *data)
{
	if (!tokens || !*tokens)
		return (NULL);
	return (manage_pipe(tokens, data));
}
