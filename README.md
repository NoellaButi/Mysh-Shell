# mysh – A Simple Shell (CS360 Assignment 1)

This project implements a minimal shell (`mysh`) in C as part of the CS360 Operating Systems course. It supports basic built-in commands and executes external commands using `fork`, `execvp`, and `wait`.

## Features

- **Built-in commands:**
  - `cd [directory]`: Change the current working directory
  - `pwd`: Print the current working directory
  - `exit`: Exit the shell
- **External command execution** using:
  - `fork()`
  - `execvp()`
  - `wait()`
- **Dynamic prompt** that displays the current working directory

## Files

- `mysh.c`: Main C source code
- `Makefile`: To compile the shell using `make`

## Concepts Practiced

- Process creation and management in Unix
- Executing programs from within a shell
- System calls: `fork`, `execvp`, `wait`, `getcwd`, `chdir`
- Simple command parsing and prompt formatting

## Notes

- The shell handles invalid commands gracefully with error messages.
- Exits cleanly on Ctrl+D or typing exit.

## How to Compile and Run

```bash
make
./mysh
