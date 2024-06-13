/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmikhayl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 17:04:22 by rmikhayl          #+#    #+#             */
/*   Updated: 2024/06/06 18:13:53 by rmikhayl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"

char	*check_heredoc(char *line)
{
	char	**parsed;

	parsed = ft_split(line, ' ');
	if (!ft_strcmp(parsed[0], "cat") && !ft_strcmp(parsed[1], "<<"))
		return (heredoc("EOF"));
	else
		return (line);
}

char	*heredoc(char *eof)
{
	char	*line;
	char	*comb;

	comb = "";
	while (1)
	{
		line = readline("heredoc>");
		if (!ft_strcmp(line, eof))
			return (comb);
		comb = ft_strjoin(ft_strjoin(comb, line), "\n");
		free(line);
	}
}
