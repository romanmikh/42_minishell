# include "tokens.h"

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
		ft_printf("input[%d] ->  %s \n", i, current_node->data);
		current_node = current_node->next;
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

