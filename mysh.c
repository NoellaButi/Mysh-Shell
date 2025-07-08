// mysh.c
// A simple shell program for CS360 Assignment 1
// Supports built-in commands (cd, pwd, exit) and external commands via fork/execvp

#include <stdio.h>      // for printf, fgets, perror
#include <stdlib.h>     // for exit
#include <unistd.h>     // for getcwd, chdir, fork, execvp
#include <string.h>     // for string manipulation
#include <sys/wait.h>   // for wait
#include <errno.h>      // for error reporting

#define MAX_INPUT 256   // Max input length for one command line

int main() {
    char input[MAX_INPUT];        // buffer for user input
    char input_copy[MAX_INPUT];   // copy of input for tokenizing
    char cwd[1024];               // current working directory path

    while (1) {
        // Display shell prompt with current directory
        if (getcwd(cwd, sizeof(cwd)) == NULL) {
            perror("getcwd error");
            exit(1);
        }

        printf("%s$mysh> ", cwd);
        fflush(stdout); // ensures the prompt prints immediately

        // Read user input
        if (fgets(input, sizeof(input), stdin) == NULL) {
            printf("\n"); // graceful exit on Ctrl+D
            break;
        }

        // Remove newline character
        input[strcspn(input, "\n")] = 0;

        // Make a copy of the input for safe tokenization
        strcpy(input_copy, input);

        // --- Built-in Commands ---

        // Exit command
        if (strcmp(input, "exit") == 0) {
            exit(0);
        }

        // pwd command (print current directory)
        else if (strcmp(input, "pwd") == 0) {
            if (getcwd(cwd, sizeof(cwd)) != NULL) {
                printf("%s\n", cwd);
            } else {
                perror("getcwd error");
            }
        }

        // cd command (change directory)
        else if (strncmp(input, "cd ", 3) == 0) {
            char *path = input + 3; // extract path from "cd path"
            if (chdir(path) != 0) {
                perror("cd error");
            }
        }

        // --- External Commands ---
        else {
            // Split input_copy into command + arguments
            char *args[MAX_INPUT / 2 + 1]; // enough for typical use
            int i = 0;
            char *token;
            char *saveptr;

            token = strtok_r(input_copy, " ", &saveptr);
            while (token != NULL) {
                args[i++] = token;
                token = strtok_r(NULL, " ", &saveptr);
            }
            args[i] = NULL; // terminate array

            // Fork a child process
            int pid = fork();
            if (pid < 0) {
                // fork failed
                perror("Failed to create process");
            }
            else if (pid == 0) {
                // child process: execute command
                if (execvp(args[0], args) == -1) {
                    perror("Failed to execute command");
                }
                exit(EXIT_FAILURE); // exit if exec fails
            }
            else {
                // parent process: wait for child
                wait(NULL);
            }
        }
    }

    return 0;
}
