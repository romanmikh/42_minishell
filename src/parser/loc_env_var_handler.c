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

void	handle_local_vars(t_ms_data *data, char *arg);
char	*process_argument(char *arg, t_ms_data *data);

int count_elements(char **array) {
    int count = 0;
    while (array && array[count]) {
        count++;
    }
    return count;
}

void post_process_command_args(t_ast *command_node, int arg_count, t_ms_data *data) {
    int i = 0;
    char *processed_arg;
    char **split_arg = NULL;
    int current_size = arg_count;  // Start with the initially allocated size.

    while (i < current_size) {
        if (!is_in_single_quotes(command_node->args[i])) {
            handle_local_vars(data, command_node->args[i]);
            processed_arg = process_argument(command_node->args[i], data);
        } else {
            processed_arg = ft_substr(command_node->args[i], 1, ft_strlen(command_node->args[i]) - 2);
        }
        free(command_node->args[i]);

        // Split the processed argument
        split_arg = ft_split(processed_arg, ' ');
        int split_count = count_elements(split_arg);  // Get the number of split elements

        // Reallocate if necessary to accommodate the new arguments
        if (split_count > 1) {
            int required_size = i + split_count;  // Calculate how much space we need
            if (required_size > current_size) {
                current_size = required_size;
                command_node->args = realloc(command_node->args, sizeof(char *) * (current_size + 1));
                if (!command_node->args) {
                    // Handle allocation failure
                    perror("Realloc failed");
                    exit(1);
                }
            }
            
            // Add split arguments to command_node->args
            for (int j = 0; j < split_count; j++) {
                command_node->args[i + j] = ft_strdup(split_arg[j]);
            }
            i += split_count;  // Move index by the number of new arguments added
        } else {
            command_node->args[i] = ft_strdup(processed_arg);
            i++;
        }

        // Free split_arg array and processed_arg
        for (int j = 0; split_arg[j]; j++) {
            free(split_arg[j]);
        }
        free(split_arg);
        free(processed_arg);
    }

    command_node->args[current_size] = NULL;  // Null-terminate the args array
    final_quote_removal(current_size, command_node);
}

void	handle_local_vars(t_ms_data *data, char *arg)
{
	char	*p;
	int		valid_var;

	p = arg;
	valid_var = 1;
	if (arg[0] != '=' && ft_strchr(arg, '='))
	{
		while (p < ft_strchr(arg, '='))
		{
			if (!ft_isalnum(*p++))
			{
				valid_var = 0;
				break ;
			}
		}
		if (valid_var)
			handle_add_set_shell_variable(&data->shell_variables, arg);
	}
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
	ft_printf(YEL"processed_arg: '%s'\n"RESET, processed_arg);
	fflush(stdout);
	return (processed_arg);
}
