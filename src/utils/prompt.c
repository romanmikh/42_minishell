/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmikhayl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 13:58:23 by rmikhayl          #+#    #+#             */
/*   Updated: 2024/06/17 16:06:24 by dmdemirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include "env.h"

/*
todo: 
extract and print only after LOGNAME

!wrong example:
🌴 dmdemirk@maxishell:~/home/dmdemirk/Documents/minishell>

correct example:
🌴 dmdemirk@maxishell:~/Documents/minishell>
 */

char *generate_prompt(t_minishell_data *data);
char *generate_prompt_string(t_minishell_data *data, char *pwd, char *home_dir);

char *generate_prompt(t_minishell_data *data)
{
    char *prompt;
    size_t prompt_len;
    char *pwd;
    char *home_dir;

	home_dir = NULL;
	pwd = NULL;
    pwd = generate_prompt_string(data, pwd, home_dir);
    prompt_len = ft_strlen("🌴\e[1m @maxishell:~> \e[m") + \
                 ft_strlen(get_env(data->envp, "LOGNAME")) + \
                 ft_strlen(pwd) + \
                 1;
    prompt = (char *)malloc(prompt_len);
    if (!prompt)
        exit(EXIT_FAILURE);
    ft_strcpy(prompt, "🌴\e[1m ");
    ft_strcat(prompt, get_env(data->envp, "LOGNAME"));
    ft_strcat(prompt, "@maxishell:");
    ft_strcat(prompt, pwd);
    ft_strcat(prompt, "> \e[m");
    return (prompt);
}

char *generate_prompt_string(t_minishell_data *data, char *pwd, char *home_dir)
{
    char *temp_pwd;


    pwd = get_env(data->envp, "PWD");
    if (pwd)
    {
        home_dir = get_env(data->envp, "HOME");
        if (home_dir && ft_strncmp(pwd, home_dir, ft_strlen(home_dir)) == 0)
        {
            temp_pwd = ft_strjoin("~", pwd + ft_strlen(home_dir));
            free(pwd);
            pwd = temp_pwd;
        }
    }
    return pwd;
}