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
#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <pwd.h>

void	add_node(t_token **head, char *str)
{
	t_token	*new_node;	
	t_token	*curr_node;

	new_node = (t_token *)malloc(sizeof(t_token));
	if (!new_node)
		return ;
	new_node->data = str;
	new_node->next = NULL;
	if (*head == NULL)
	{
		*head = new_node;
		return ;
	}
	curr_node = *head;
	while (curr_node->next != NULL)
		curr_node = curr_node->next;
	curr_node->next = new_node;
}

void	print_stack(t_token **stack)
{
  t_token *current_node;
  int   i;

  i = 0;
	current_node = *stack;
	while (current_node != NULL)
	{
		printf("argv[%d] ->  %s \n", i, current_node->data);
		current_node = current_node->next;
    i++;
	}
	printf("\n");
}

void handle_args(t_token **tokens, char **argv)
{
  int i = 1;
  
  while (argv[i])
  {
    add_node(tokens, argv[i]);
    i++;
  }
}


int	main(int argc, char **argv)
{
  char *line;
  const char *history_file = ".maxishell_history";

  read_history(history_file);

  while (1)
  {
    // getpwuid(geteuid())->pw_name // username, but using disallowed functions
    printf("\033[48;5;236m");
    line = readline("user@maxishell$ ");

    if (!line)
      break;
    if (*line)
      add_history(line);
    write_history(history_file);
    printf("@maxishell: command not found: %s\n", ft_split(line, ' ')[0]);
  }
  
  t_token *tokens = NULL;
  printf("argc -> %d\n", argc);
  free(line);
  handle_args(&tokens, argv);
  print_stack(&tokens);  
  return (0);
}

