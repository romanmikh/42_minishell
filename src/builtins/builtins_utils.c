/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rocky <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 14:23:42 by rocky             #+#    #+#             */
/*   Updated: 2024/11/06 14:23:44 by rocky            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>
#include "env.h"
#include "exit_status.h"
#include "tokens.h"
#include "signals.h"
#include "builtins.h"

void	free_signal_context(void)
{
	t_signal_context	*context;

	context = get_context(NULL);
	free(context);
}

void	clear_history_file(void)
{
	remove(HISTORY_PATH);
}
