*This project has been created as part of the 42 curriculum by gabrgarc, mmaquine.*

# Minishell

## Description
The goal of this project is to create a simple, yet functional, shell in C, mirroring the basic behavior of bash. This project delves deep into process creation, file descriptors, and robust parsing techniques. 

In our implementation, the shell processes user input by lexical analysis and builds an Abstract Syntax Tree (AST) using a binary tree structure to manage command execution logic, pipes, and redirections. Environment variables are efficiently managed and expanded using a custom hash table structure. The project fully supports heredoc redirections, implemented via `get_next_line` and temporary files, ensuring reliable input reading.

## Instructions

### Prerequisites
This project is designed to run on Unix/Linux systems. Ensure you have `gcc`, `make`, and the **GNU Readline library** installed:

```bash
sudo apt-get update
sudo apt-get install build-essential libreadline-dev
```

### Installation & Execution

**1. Clone the repository:**

```bash
git clone https://github.com/GabrielGem/minishell.git
cd minishell
```

**2. Compile the program:**

```bash
make
```

**3. Run the shell:**

```bash
./minishell
```

## Resources

### Tutorials

* **[Minishell Video Tutorials](https://www.youtube.com/playlist?list=PLr93_hd_KSoJukNfwkr6uOBG77uZw7T1c):** A curated YouTube playlist covering essential concepts and implementations relevant to building this project.

### Documentation & Articles

* **Data Structures Using C - Chapter 12 (Trees):** Documentation used as a theoretical foundation for implementing the binary tree structure of our Abstract Syntax Tree (AST).
* **[Write a Shell in C - Stephen Brennan](https://brennan.io/2015/01/16/write-a-shell-in-c/):** A comprehensive guide on the basic loop, parsing, and execution logic of a custom shell.
* **Bash Reference Manual:** The primary source of truth for shell behavior, grammar, and built-in rules.
* **GNU Readline Library:** Documentation used for handling the prompt, command history, and input reading.

### AI Usage

* **Project Architecture & Workflow:** AI tools were used to establish the folder structure, logically separate the header files, and design a modular `Makefile`. This architectural setup was crucial in organizing and facilitating our pair programming workflow.

## Usage Examples

Below are a few examples of commands you can run in our Minishell, demonstrating its capability to handle multiple pipes, filters, and standard external commands:

**1. Listing only directories in the current folder:**

```bash
ls -la | grep ^d
```

**2. Counting the number of processing units (threads/cores):**

```bash
cat /proc/cpuinfo | grep process | wc -l
```

**3. Exiting the shell:**

```bash
exit
```

## Technical Choices

* **Hash Table for Environment Variables:** We implemented a hash table to store, search, and manipulate environment variables efficiently. This structure ensures fast data retrieval and modification, which is crucial when expanding variables and handling built-ins like `export` and `unset`.
* **Abstract Syntax Tree (AST):** The parsed user input is converted into a binary Abstract Syntax Tree. This structure dictates the exact execution order and hierarchy of the commands, making it highly robust and logical to handle complex command lines involving pipes (`|`) and multiple redirections.
* **Dispatch Table:** To manage our built-in commands, we utilized a dispatch table (an array of function pointers). This design pattern replaces lengthy and repetitive `if-else` statement chains, allowing the program to map command strings directly to their corresponding execution functions cleanly.
* **Emulated Polymorphism in C:** A core architectural highlight of this project is the emulation of polymorphism in C. By structuring our AST nodes carefully (often using base structs and typecasting), we were able to treat different types of nodes (e.g., execution nodes, pipe nodes, redirection nodes) uniformly during the tree traversal and execution phases. This resulted in a highly modular, scalable, and elegant codebase.