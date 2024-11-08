/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loc_env_var_handler.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmikhayl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 16:46:53 by rmikhayl          #+#    #+#             */
/*   Updated: 2024/09/09 16:19:56 by dmdemirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tokens.h>
#include "libft.h"

void	handle_local_vars(t_ms_data *data, char *arg);
char	*process_argument(char *arg, t_ms_data *data);

void	handle_split_allocation(t_ast *command_node, int *current_size, \
									int required_size)
{
	if (required_size > *current_size)
	{
		command_node->args = ft_realloc_array(command_node->args, \
												*current_size, required_size);
		*current_size = required_size;
	}
}

void	split_loc_vars(t_ast *command_node, char *processed_arg, \
						int *current_size, int *i)
{
	char	**split_arg;
	int		split_count;
	int		required_size;
	int		j;

	split_arg = ft_split_preserve_quotes(processed_arg, ' ');
	split_count = ft_len_2d_arr(split_arg);
	if (split_count > 1)
	{
		required_size = *i + split_count;
		handle_split_allocation(command_node, current_size, required_size);
		j = 0;
		while (j < split_count)
		{
			command_node->args[*i + j] = ft_strdup(split_arg[j]);
			j++;
		}
		*i += split_count;
	}
	else
	{
		command_node->args[*i] = ft_strdup(processed_arg);
		(*i)++;
	}
	if (split_arg != NULL)
		ft_free_2d_arr(split_arg);
}

void	post_process_command_args(t_ast *command_node, int arg_count, \
									t_ms_data *data)
{
	int		i;
	char	*processed_arg;
	int		current_size;
	char	*tmp_proc_arg;

	i = 0;
	tmp_proc_arg = NULL;
	current_size = arg_count;
	while (i < current_size)
	{
		if (!is_in_single_quotes(command_node->args[i]))
		{
			handle_local_vars(data, command_node->args[i]);
			tmp_proc_arg = process_argument(command_node->args[i], data);
		}
		else
			tmp_proc_arg = ft_substr(command_node->args[i], 1, \
										ft_strlen(command_node->args[i]) - 2);
		free(command_node->args[i]);
		processed_arg = ft_remove_quotes(tmp_proc_arg, '\"');
		free(tmp_proc_arg);
		split_loc_vars(command_node, processed_arg, &current_size, &i);
		free(processed_arg);
	}
	command_node->args[current_size] = NULL;
}

char	*append_expanded_var(char *processed_arg, char *tmp_ad, \
			char *expanded_var)
{
	char	*tmp;
	char	*tmp_2;

	tmp = ft_strjoin_free(processed_arg, expanded_var);
	tmp_ad = tmp_adj(tmp);
	free(expanded_var);
	tmp_2 = ft_strdup(tmp_ad);
	free(tmp_ad);
	return (tmp_2);
}

char	*process_argument(char *arg, t_ms_data *data)
{
	char	*start;
	char	*processed_arg;
	char	*tmp_ad;
	char	*expanded_var;

	tmp_ad = NULL;
	processed_arg = ft_strdup("");
	start = arg;
	while (*start != '\0')
	{
		if (*start == '$')
		{
			expanded_var = expand_variable(&start, data);
			if (expanded_var != NULL)
			{
				processed_arg = append_expanded_var(processed_arg, \
									tmp_ad, expanded_var);
				free(tmp_ad);
			}
		}
		else
			processed_arg = append_literal(&start, processed_arg);
	}
	return (processed_arg);
}
