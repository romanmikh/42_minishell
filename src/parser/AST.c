///* ************************************************************************** */
///*                                                                            */
///*                                                        :::      ::::::::   */
///*   AST.c                                              :+:      :+:    :+:   */
///*                                                    +:+ +:+         +:+     */
///*   By: rmikhayl <marvin@42.fr>                    +#+  +:+       +#+        */
///*                                                +#+#+#+#+#+   +#+           */
///*   Created: 2024/06/07 15:51:30 by rmikhayl          #+#    #+#             */
///*   Updated: 2024/06/07 15:51:45 by rmikhayl         ###   ########.fr       */
///*                                                                            */
///* ************************************************************************** */
//
////#include "tokens.h"
//
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <unistd.h>
//#include <sys/wait.h>
//#include <fcntl.h>
//
//#define MAX_TOKENS 100
//
//// Tokenize the input string
//char **tokenize(char *input) {
//    printf("Tokenizing input: %s\n", input);
//    
//    char **tokens = malloc(MAX_TOKENS * sizeof(char *));
//    char *token = strtok(input, " ");
//    int i = 0;
//
//    while (token != NULL) {
//        tokens[i++] = strdup(token);
//        token = strtok(NULL, " ");
//    }
//
//    tokens[i] = NULL; // Null-terminate the list of tokens
//
//    // Print tokens
//    printf("Tokens:\n");
//    for (int j = 0; j < i; j++) {
//        printf("  Token[%d]: %s\n", j, tokens[j]);
//    }
//    return tokens;
//}
//
//typedef enum {
//    COMMAND,
//    PIPE,
//    REDIRECTION,
//    SEQUENCE
//} NodeType;
//
//typedef struct ASTNode {
//    NodeType type;
//    char **command;  // Only for COMMAND nodes
//    char *file;      // Only for REDIRECTION nodes
//    struct ASTNode *left;
//    struct ASTNode *right;
//} ASTNode;
//
//// Helper functions to create nodes
//ASTNode *create_command_node(char **command) {
//    ASTNode *node = malloc(sizeof(ASTNode));
//    node->type = COMMAND;
//    node->command = command;
//    node->left = NULL;
//    node->right = NULL;
//
//    // Print node creation
//    printf("Created COMMAND node with command: ");
//    for (int i = 0; command[i] != NULL; i++) {
//        printf("%s ", command[i]);
//    }
//    printf("\n");
//
//    return node;
//}
//
//ASTNode *create_pipe_node(ASTNode *left, ASTNode *right) {
//    ASTNode *node = malloc(sizeof(ASTNode));
//    node->type = PIPE;
//    node->left = left;
//    node->right = right;
//
//    // Print node creation
//    printf("Created PIPE node\n");
//
//    return node;
//}
//
//ASTNode *create_redirection_node(ASTNode *left, char *file) {
//    ASTNode *node = malloc(sizeof(ASTNode));
//    node->type = REDIRECTION;
//    node->left = left;
//    node->right = NULL;
//    node->file = strdup(file);
//
//    // Print node creation
//    printf("Created REDIRECTION node to file: %s\n", file);
//
//    return node;
//}
//
//// Parse tokens into an AST
//ASTNode *parse_tokens(char **tokens) {
//    printf("Parsing tokens into AST...\n");
//
//    ASTNode *current = NULL;
//    char **command = NULL;
//    int i = 0;
//    int cmd_start = 0;
//
//    while (tokens[i] != NULL) {
//        if (strcmp(tokens[i], "|") == 0) {
//            command = malloc((i - cmd_start + 1) * sizeof(char *));
//            for (int j = cmd_start; j < i; j++) {
//                command[j - cmd_start] = tokens[j];
//            }
//            command[i - cmd_start] = NULL;
//
//            ASTNode *cmd_node = create_command_node(command);
//            if (current == NULL) {
//                current = cmd_node;
//            } else {
//                current = create_pipe_node(current, cmd_node);
//            }
//
//            cmd_start = i + 1;
//        } else if (strcmp(tokens[i], ">") == 0) {
//            command = malloc((i - cmd_start + 1) * sizeof(char *));
//            for (int j = cmd_start; j < i; j++) {
//                command[j - cmd_start] = tokens[j];
//            }
//            command[i - cmd_start] = NULL;
//
//            ASTNode *cmd_node = create_command_node(command);
//            ASTNode *redirection_node = create_redirection_node(cmd_node, tokens[i + 1]);
//            current = redirection_node;
//            i++; // Skip the next token (filename)
//            cmd_start = i + 1;
//        } else if (strcmp(tokens[i], ">>") == 0) {
//            command = malloc((i - cmd_start + 1) * sizeof(char *));
//            for (int j = cmd_start; j < i; j++) {
//                command[j - cmd_start] = tokens[j];
//            }
//            command[i - cmd_start] = NULL;
//
//            ASTNode *cmd_node = create_command_node(command);
//            ASTNode *redirection_node = create_redirection_node(cmd_node, tokens[i + 1]);
//            redirection_node->type = REDIRECTION; // Set to append mode
//            current = redirection_node;
//            i++; // Skip the next token (filename)
//            cmd_start = i + 1;
//        } else if (strcmp(tokens[i], "<") == 0) {
//            command = malloc((i - cmd_start + 1) * sizeof(char *));
//            for (int j = cmd_start; j < i; j++) {
//                command[j - cmd_start] = tokens[j];
//            }
//            command[i - cmd_start] = NULL;
//
//            ASTNode *cmd_node = create_command_node(command);
//            ASTNode *redirection_node = create_redirection_node(cmd_node, tokens[i + 1]);
//            redirection_node->type = SEQUENCE; // Set to input redirection
//            current = redirection_node;
//            i++; // Skip the next token (filename)
//            cmd_start = i + 1;
//        }
//        i++;
//    }
//
//    if (tokens[cmd_start] != NULL && current == NULL) {
//        command = malloc((i - cmd_start + 1) * sizeof(char *));
//        for (int j = cmd_start; j < i; j++) {
//            command[j - cmd_start] = tokens[j];
//        }
//        command[i - cmd_start] = NULL;
//
//        ASTNode *cmd_node = create_command_node(command);
//        if (current == NULL) {
//            current = cmd_node;
//        } else {
//            current = create_pipe_node(current, cmd_node);
//        }
//    }
//
//    printf("AST parsing complete.\n");
//    return current;
//}
//
//// Helper function to execute commands
//void execute_command(char **command) {
//    printf("Executing command: ");
//    for (int i = 0; command[i] != NULL; i++) {
//        printf("%s ", command[i]);
//    }
//    printf("\n");
//
//    if (execvp(command[0], command) == -1) {
//        perror("execvp");
//        exit(EXIT_FAILURE);
//    }
//}
//
//void execute_redirection(ASTNode *node) {
//    printf("Executing redirection to file: %s\n", node->file);
//
//    int fd;
//    if (node->type == REDIRECTION) {
//        fd = open(node->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
//    } else {
//        fd = open(node->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
//    }
//    
//    if (fd == -1) {
//        perror("open");
//        exit(EXIT_FAILURE);
//    }
//
//    if (dup2(fd, STDOUT_FILENO) == -1) {
//        perror("dup2");
//        exit(EXIT_FAILURE);
//    }
//
//    close(fd);
//    execute_command(node->left->command);
//}
//
//void execute_input_redirection(ASTNode *node) {
//    printf("Executing input redirection from file: %s\n", node->file);
//
//    int fd = open(node->file, O_RDONLY);
//    if (fd == -1) {
//        perror("open");
//        exit(EXIT_FAILURE);
//    }
//
//    if (dup2(fd, STDIN_FILENO) == -1) {
//        perror("dup2");
//        exit(EXIT_FAILURE);
//    }
//
//    close(fd);
//    execute_command(node->left->command);
//}
//
//void execute_pipe(ASTNode *left, ASTNode *right) {
//    printf("Executing pipe\n");
//
//    int pipefd[2];
//    if (pipe(pipefd) == -1) {
//        perror("pipe");
//        exit(EXIT_FAILURE);
//    }
//
//    pid_t pid = fork();
//    if (pid == -1) {
//        perror("fork");
//        exit(EXIT_FAILURE);
//    }
//
//    if (pid == 0) { // Child process
//        close(pipefd[0]);
//        if (dup2(pipefd[1], STDOUT_FILENO) == -1) {
//            perror("dup2");
//            exit(EXIT_FAILURE);
//        }
//        close(pipefd[1]);
//        execute_command(left->command);
//    } else { // Parent process
//        close(pipefd[1]);
//        if (dup2(pipefd[0], STDIN_FILENO) == -1) {
//            perror("dup2");
//            exit(EXIT_FAILURE);
//        }
//        close(pipefd[0]);
//        execute_command(right->command);
//        waitpid(pid, NULL, 0);
//    }
//}
//
//// Main execution function
//void execute_ast(ASTNode *node) {
//    if (node == NULL) {
//        return;
//    }
//
//    if (node->type == COMMAND) {
//        execute_command(node->command);
//    } else if (node->type == REDIRECTION) {
//        execute_redirection(node);
//    } else if (node->type == SEQUENCE) {
//        execute_input_redirection(node);
//    } else if (node->type == PIPE) {
//        execute_pipe(node->left, node->right);
//    }
//}
//
//int main() {
//    char input[256];
//    printf("Welcome to minishell!\n");
//
//    while (1) {
//        printf("minishell> ");
//        if (fgets(input, sizeof(input), stdin) == NULL) {
//            break;
//        }
//
//        // Remove trailing newline character
//        input[strcspn(input, "\n")] = '\0';
//
//        char **tokens = tokenize(input);
//        ASTNode *ast = parse_tokens(tokens);
//
//        if (ast != NULL) {
//            execute_ast(ast);
//        }
//
//        // Free tokens and AST (not shown here for brevity)
//    }
//
//    printf("Exiting minishell.\n");
//    return 0;
//}
