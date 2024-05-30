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
		printf("input[%d] ->  %s \n", i, current_node->data);
		current_node = current_node->next;
    i++;
	}
}

void handle_args(t_token **tokens, char **argv)
{
  int i = 0;
  
  while (argv[i])
  {
    add_node(tokens, argv[i]);
    i++;
  }
}

void	free_stack(t_token **stack)
{
	t_token	*current;
	t_token	*next;

	current = *stack;
	while (current != NULL)
	{
		next = current->next;
		free(current);
		current = next;
	}
}

int	main()
{
  // Initialisation & load configs
  char *line;
  const char *history_file = "./utils/.maxishell_history";
  t_token *tokens = NULL;

  read_history(history_file);
  // Run command loop
  while (1)
  {
    // getpwuid(geteuid())->pw_name // username, but using disallowed functions
    printf("\033[48;5;236m");
    line = readline("🌴 dimrom@maxishell$ ");

    if (!line)
      break;
    if (*line)
      add_history(line);
    write_history(history_file);
    printf("@maxishell: command not found: %s\n", ft_split(line, ' ')[0]);

    // Handle arguments
    handle_args(&tokens, ft_split(line, ' '));
    print_stack(&tokens);

    // Free linked list & line for next input
    free_stack(&tokens);
    free(line);
  }
  
  // Perform shutdown/cleanup
  return (0);
}

