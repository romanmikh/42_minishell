/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmdemirk <dmdemirk@student.42london.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:05:18 by dmdemirk          #+#    #+#             */
/*   Updated: 2024/05/30 13:05:38 by dmdemirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"

void handle_args(t_token **tokens, char **argv)
{
  int i = 0;
  
  while (argv[i])
  {
    add_node(tokens, argv[i]);
    i++;
  }
}

int	main()
{
  // Initialisation & load configs
  char *line;
  const char *history_file = "./utils/.maxishell_history";
  t_token *tokens;

  read_history(history_file);
  // Run command loop
  int repeat = 1;
  while (repeat)
  {
    tokens = NULL;
    // getpwuid(geteuid())->pw_name // username, but uses disallowed functions
    line = readline("🌴\e[1m dimrom@maxishell> \e[m");

    if (!line || ft_strcmp(line, "exit") == 0)
      break;
    if (*line)
      add_history(line);
    write_history(history_file);

    char **parsed_text = ft_split(line, ' ');
    printf("\033[31m@maxishell: command not found: %s\033[0m\n", parsed_text[0]);

    // Handle arguments
    handle_args(&tokens, parsed_text);

    // Free linked list & line for next input
    print_stack(&tokens);
    free_stack(&tokens);
    free(line);
  }
  
  // Perform shutdown/cleanup
  return (0);
}

