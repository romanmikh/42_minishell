/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmdemirk <dmdemirk@student.42london.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 16:46:20 by dmdemirk          #+#    #+#             */
/*   Updated: 2024/06/10 17:22:59 by dmdemirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <assert.h>
#include "libft.h"
#include "env.h"
#include "shell.h"
#include <stdio.h>

void	env_tests(t_ms_data *data, char **envp);
void	test_init_env(t_ms_data *data, char **envp);
void	test_get_env(t_ms_data *data, char **envp);
void	test_set_env(t_ms_data *data, char **envp);
void	test_unset_env(t_ms_data *data);

void	env_tests(t_ms_data *data, char **envp)
{
	ft_printf("\nENV TESTS\n");
	test_init_env(data, envp);
	test_get_env(data, envp);
	test_set_env(data, envp);
	test_unset_env(data);
	free_env(data->envp);
}

void	test_init_env(t_ms_data *data, char **envp)
{
	char	**test_envp;
	int		envp_count;
	int		test_envp_count;

	data->envp = NULL;
	init_env(&data->envp, envp);
	test_envp = env_to_array(data->envp);
	envp_count = 0;
	while (envp[envp_count])
		envp_count++;
	test_envp_count = 0;
	while (test_envp[test_envp_count])
		test_envp_count++;
	assert(envp_count == test_envp_count);
	ft_printf("\033[0m");
	ft_printf("\033[0;32m");
	ft_printf("init_env    -> OK\n");
	ft_printf("\033[0m");
}

void	test_get_env(t_ms_data *data, char **envp)
{
	char	*value;

	data->envp = NULL;
	init_env(&data->envp, envp);
	value = get_env(data->envp, "LOGNAME");
	assert(value != NULL);
	assert(ft_strcmp(value, getenv("LOGNAME")) == 0);
	ft_printf("\033[0m");
	ft_printf("\033[0;32m");
	ft_printf("get_env     -> OK\n");
	ft_printf("\033[0m");
}

void	test_set_env(t_ms_data *data, char **envp)
{
	char	*value;

	data->envp = NULL;
	init_env(&data->envp, envp);
	set_env(&data->envp, "TEST", "test");
	value = get_env(data->envp, "TEST");
	assert(value != NULL);
	assert(ft_strcmp(value, "test") == 0);
	ft_printf("\033[0m");
	ft_printf("\033[0;32m");
	ft_printf("set_env     -> OK\n");
	ft_printf("\033[0m");
}

void	test_unset_env(t_ms_data *data)
{
	char	*value;

	set_env(&data->envp, "TEST", "test");
	value = get_env(data->envp, "TEST");
	assert(value != NULL);
	assert(ft_strcmp(value, "test") == 0);
	unset_env(&data->envp, "TEST");
	value = get_env(data->envp, "TEST");
	assert(value == NULL);
	ft_printf("\033[0m");
	ft_printf("\033[0;32m");
	ft_printf("unset_env   -> OK\n");
	ft_printf("\033[0m");
}
