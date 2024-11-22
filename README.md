![image](https://github.com/user-attachments/assets/4e173ce6-fd1d-49a4-8515-9a918f0f8a9d)


![Norminette workflow](https://github.com/dimadem/minishell/actions/workflows/norminette.yml/badge.svg)
![Compilation workflow](https://github.com/dimadem/minishell/actions/workflows/compile.yml/badge.svg)
![Valgrind workflow](https://github.com/dimadem/minishell/actions/workflows/valgrind.yml/badge.svg)


# 42 Minishell Project 🐚

Welcome to the **42 Minishell** project! This project our minimalist shell implementation designed to mimic features of `bash`. It supports various shell features, including pipes, environment variables, built-in commands, and more. 🚀

## Features

- **Basic Shell Functions**: Command execution, redirections, and pipes (`|`).
- **Environment & Loval Variables**: Handles `$VAR` expansions.
- **Built-in Commands**: Includes `cd`, `echo`, `env`, `export`, `pwd`, `unset`, and `exit`.
- **Signal Handling**: Graceful handling of `Ctrl+C`, `Ctrl+\`, and `Ctrl+D`.
- **Error Handling**: Displays clear messages for invalid inputs or syntax errors.
- **Custom Memory Management**: Implements robust memory safety mechanisms.

## Installation and Usage

To compile and run the project, follow these steps:

1. Clone the repository:
   ```
   git clone git@github.com:dimadem/minishell.git minishell
   cd minishell
   make
   ./minishell
   ```
2. Please see documentation for this project under https://dimadem.github.io/minishell/

3. The project uses an Abstract Syntax Tree (AST) to recursively enforce the correct order of execution for commands. This ensures proper parsing and execution logic, even for complex pipelines and redirections.

4. High-level project architecture:

   - **build/**: Directory for object files and other intermediate build artifacts.
   - **docs/**: Documentation for the project.
   - **inc/**: Header files for the project, defining interfaces for different modules:
     - `builtins.h`: Declarations for built-in shell commands.
     - `execute.h`: Declarations for command execution functions.
     - `parser.h`: Declarations for command-line parsing functions.
     - `pipe.h`: Declarations for piping functions.
     - `redirection.h`: Declarations for redirection functions.
     - `shell.h`: General declarations for the shell.
     - `tokens.h`: Declarations for token parsing functions.
   - **lib/**: Directory for third-party libraries, such as libft.
   - **src/**: Source files for the project, organized into subdirectories by functionality:
     - **builtins/**: Implementation of built-in shell commands.
     - **execute/**: Implementation of command execution logic.
     - **parser/**: Implementation of command-line parsing.
     - **pipe/**: Implementation of piping between commands.
     - **redirection/**: Implementation of input/output redirection.
     - **utils/**: Implementation of auxiliary functions.
     - **test/**: Tests for project components.
     - `main.c`: Entry point of the shell application.

## Conclusion

The 42 Minishell project delves into system-level programming, process management, and advanced parsing. It provides a foundation for further OS-level development.