*This project has been created as part of the 42 curriculum by jille, esezalor.*

# Minishell

## Description
The goal of Minishell is to create a basic command-line interface that mimics the behavior of Bash. It involves parsing user input, managing environment variables, handling redirections (<, >, <<, >>), and pipes (|). This project provides deep insight into process management (forks, wait), file descriptors, and the inner workings of a system's execution loop.

## Instructions
To compile and run the project:

1. make
2. ./minishell 

Example:
```bash
 ./minishell
```


## Features

* Display a prompt when waiting for a new command.
* Working history.
* Execute executables based on the PATH or relative/absolute paths.
* Built-ins: echo, cd, pwd, export, unset, env, exit.
* Signal handling (Ctrl-C, Ctrl-D, Ctrl-\\).

## Resources
* [The Linux Programming interface](https://broman.dev/download/The%20Linux%20Programming%20Interface.pdf)
* [Bash Reference Manual | Edition 5.3, for Bash Version 5.3. | May 2025](https://www.gnu.org/software/bash/manual/bash.pdf)
* [GNU C Library](https://www.gnu.org/software/libc/)

AI was used to generate the initial README structure.