<!-- [image](https://github.com/user-attachments/assets/4e173ce6-fd1d-49a4-8515-9a918f0f8a9d) -->

![Norminette workflow](https://github.com/dimadem/minishell/actions/workflows/norminette.yml/badge.svg)
![Compilation workflow](https://github.com/dimadem/minishell/actions/workflows/compile.yml/badge.svg)
![Valgrind workflow](https://github.com/dimadem/minishell/actions/workflows/valgrind.yml/badge.svg)


# 42 Minishell Project 🐚

**Minishell** is our minimalist `bash` shell implementation coded **entirely in C**.

<!-- Centered image -->
<p align="center">
  <img src="https://github.com/user-attachments/assets/4e173ce6-fd1d-49a4-8515-9a918f0f8a9d" alt="Description">
</p>


- **Command execution, redirections, and pipes (`|`)**: 
- **Environment & Local Variables**
- **cd`, `echo`, `env`, `export`, `pwd`, `unset`, and `exit`**
- **Gradeful Signal Handling**: `Ctrl+C`, `Ctrl+\`, and `Ctrl+D`.
- **Error Handling**
- **Robust Memory Management**

## Installation and Usage

1. SSH:
   ```
   git clone git@github.com:dimadem/minishell.git minishell
   cd minishell
   make
   ./minishell
   ```

2. Valgrind output saved in valgrind_out.txt after:
   ```sh
   ulimit -n 2014 # necessary once only, to address 'file descriptor too high' error
   make valgrind
   ```

3. Please see documentation for this project under https://dimadem.github.io/minishell/

4. The project uses an Abstract Syntax Tree (AST) to recursively enforce the correct order of execution for commands. This ensures proper parsing and execution logic, even for complex pipelines and redirections.

## Documentation

Full code map (almost):

![Full Code Map](./html/main_8c_a3c04138a5bfe5d72780bb7e82a18e627_cgraph.png)
