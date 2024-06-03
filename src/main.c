/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmdemirk <dmdemirk@student.42london.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:05:18 by dmdemirk          #+#    #+#             */
/*   Updated: 2024/05/31 21:09:12 by rmikhayl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"

void	handle_args(t_token **tokens, char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		add_node(tokens, argv[i]);
		i++;
	}
}

// to replace ft_split(' ') in main()
char **parse_input(char *input)
{
  int pos;
  char *token;
  char **tokens;
  char *delim;
  int bufsize;

  pos = 0;
  bufsize = 64;
  delim = " ";
  tokens = malloc(bufsize * sizeof(char *));
  if (!tokens)
  {
    ft_printf("@maxishell: allocation error\n");
    exit(EXIT_FAILURE);
  }
  while (*input)
  {
    while (*input && ft_strchr(delim, *input))
      input++;
    if (*input == '\0')
      break;
    if (*input == '\'' || *input == '\"')
    {
      char quote;
      char *start;

      quote = *input++;
      start = input;
      while (*input && *input != quote)
        input++;
      if (*input == '\0')
      {
        ft_printf("@maxishell: syntax error: unmatched %c\n", quote);
        free(tokens);
        return (NULL);
      }
      *input = '\0'; 
      token = ft_strndup(start, input - start);
      input++;
      if (ft_strlen(token) > 0)
        tokens[pos++] = token;
    }

    else if (*input == '|' || *input == '<' || *input == '>')
    {
      tokens[pos++] = ft_strndup(input, 1);
      if ((*input == '<' && *(input + 1) == '<') || (*input == '>' && *(input + 1) == '>'))
      {
        tokens[pos - 1] = ft_strndup(input, 2);
        input++;
      }
      input++;
    }
    else
    {
      char *start;

      start = input; 
      while (*input && !ft_strchr(delim, *input) && *input != '|' && *input != '<' && *input != '>' && *input != '\"' && *input != '\'')
        input++;
      token = ft_strndup(start, input - start);
      tokens[pos++] = token;
    }
  }
  tokens[pos] = NULL;
  return (tokens);
}
char *generate_prompt()
{
    char *user;
    char *pwd;
    char *prompt;
    char *s1;
    char *s2;
    char *s3;
    size_t prompt_len;

    user = getenv("LOGNAME");
    pwd = getenv("PWD");
    s1 = "🌴\e[1m ";
    s2 = "@maxishell:~";
    s3 = "> \e[m";
    prompt_len = strlen(s1) + strlen(user) + strlen(s2) + strlen(pwd) + strlen(s3) + 1;
    prompt = (char *)malloc(prompt_len);
    if (!prompt)
        exit(EXIT_FAILURE);
    ft_strcpy(prompt, s1);
    printf("%s\n", prompt);
    ft_strcat(prompt, user);
    ft_strcat(prompt, s2);
    ft_strcat(prompt, pwd);
    ft_strcat(prompt, s3);
    return (prompt);
}

int	main(void)
{
	char		*line;
	int			repeat;
	char		**arr;
	char		**parsed_text;
	t_token		*tokens;
  const char	*history_file;

  history_file = "./utils/.maxishell_history";
	read_history(history_file);
	repeat = 1;
	while (repeat)
	{

	  tokens = NULL;
  	line = readline(generate_prompt());
		if (!line || ft_strcmp(line, "exit") == 0)
			break ;
    if (*line)
	    add_history(line);
  	write_history(history_file);
		parsed_text = parse_input(line);
		if (parsed_text != NULL)
    {
      printf("\033[31m@maxishell: command not found: %s\033[0m\n", parsed_text[0]);
      fflush(stdout);
  		handle_args(&tokens, parsed_text);
  		arr = list_to_array(tokens);
  		print_stack(&tokens);
  		free_stack(&tokens);
  		free(line);
  		free(arr);
    }
	}
	return (0);
}
