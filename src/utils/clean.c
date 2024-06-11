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
#include "env.h"
void free_args(char **args) {
    if (args) {
        for (int i = 0; args[i] != NULL; i++) {
            free(args[i]);
        }
        free(args);
    }
}

void free_env_list(t_env *env) {
    t_env *temp;
    while (env) {
        free(env->key);
        free(env->value);
        temp = env;
        env = env->next;
        free(temp);
    }
}

void free_minishell_data(t_minishell_data *data) {
    if (data) {
        free_args(data->args);
        free_env_list(data->envp);
        free_env_list(data->local_env);
        free(data->current_dir);
        free(data);
    }
}

void cleanup(char *line, char **parsed_text, t_token *tokens, char *prompt) {
    free(line);
    free(parsed_text);
    free_stack(&tokens); // Ensure free_stack is implemented correctly
    free(prompt);
}
