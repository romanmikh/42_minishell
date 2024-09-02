#include "shell.h"
#include "env.h"
#include "libft.h"
#include "tokens.h"
#include <stddef.h>

int handle_add_set_shell_variable(t_env *shell_var, char *line);
int handle_get_shell_variable(t_ms_data *data, const char *key);
int handle_shell_variable(t_ast *node, t_ms_data *data);

int handle_add_set_shell_variable(t_env *shell_var, char *line)
{
    char *key;
    char *value;

    key = NULL;
    value = NULL;
    if (shell_var == NULL)
    {
        add_shell_var_node(&shell_var, line);
    }
    else
    {
        printf(GRN"we're in else of handle_add_set_shell_variable"RESET);
        key = ft_strcdup(line, '=');
        value = ft_strchr(line, '=') + 1;
        set_shell_var(&shell_var, key, value);
        free(key);
    }
    return (0);
}

int handle_get_shell_variable(t_ms_data *data, const char *key)
{
    char *value;
    t_env *shell_var;

    shell_var = data->shell_variables;
    value = get_env(shell_var, key);
    if (value)
    {
        ft_putstr_fd(value, data->std_out);
        ft_putstr_fd("\n", data->std_out);
        return (0);
    }
    return (-1);
}

int handle_shell_variable(t_ast *node, t_ms_data *data)
{
    if (node->left && node->right == NULL)
        return (handle_get_shell_variable(data, node->args[0]));
    return (-1);
}