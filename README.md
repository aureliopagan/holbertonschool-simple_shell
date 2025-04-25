# Simple Shell

## Description

This is a basic UNIX command line interpreter (shell) written in C as part of the Holberton School curriculum. It reads user input, parses it, and executes commands. It supports both interactive and non-interactive modes.

---

## How to Compile
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh

## Usage
Run the shell with
- ./hsh

Example commands
- $ ls
- $ /bin/ls
- $ echo Hello, world
- $ exit

## Features
- Executes commands with arguments
- Built-in commands: exit, env
- Resolves commands using the PATH variable
- Interactive and non-interactive mode
- Basic error handling and memory management

## Project Files
- main.h - Header file with function prototypes
- shell.c - Main shell loop
- builtins.c - Built-in command handling 
- functions.c - Utility/helper functions 
- README.md - Project documentation 
- AUTHORS - Project contributors 
- man_1_simple_shell - Manual page

## Authors
- [Valeria Bonilla](https://github.com/valeriabonilla19)
- [Aurelio Pagan](https://github.com/aureliopagan)