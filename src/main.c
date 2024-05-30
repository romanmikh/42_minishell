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
#include <readline/readline.h>
#include <readline/history.h>

void	add_node(t_token **head, char *str);


void	print_stack(t_token **stack)
{
  t_token *current_node;
  int   i;

  i = 0;
  //printf("first data in linked list is %s", stack->data);
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
    //if (*argv[i][0] == '"')
    //  handle_double_quote_arg();
//    else if (*argv[i][0] == 39) // single quote 
//      handle_single_quote();
//    else if (*argv[i][0] == '\') // single quote 
//      handle_backslash();
//    else if (*argv[i][0] == '$') // single quote 
//      handle_dollar();
    add_node(tokens, argv[i]);
    i++;
  }
}

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

int	main(int argc, char **argv)
{

  char *line;
  while (1)
  {
    line = readline("Enter a line: ");

    if (!line)
      break;
    printf("entered line: %s", line);
  }
  
  t_token *tokens = NULL;

  printf("argc -> %d\n, %s", argc, line);

  handle_args(&tokens, argv);
  printf("pass handle args\n");
  print_stack(&tokens);  
  free(line);
  return (0);
}

