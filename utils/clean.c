/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmikhayl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 17:20:07 by rmikhayl          #+#    #+#             */
/*   Updated: 2024/06/05 17:20:20 by rmikhayl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"

void	cleanup(char *line, char **parsed_text, t_token *tokens)
{
	free(line);
	free(parsed_text);
	free_stack(&tokens);
}
