#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>

extern char **environ;

/* Function prototypes */
void display_prompt(void);
char *read_input(void);
char **parse_input(char *input);
void execute_command(char **args);
int handle_builtin(char **args);
void free_args(char **args);
char *find_path(char *cmd);
void print_environment(void);

#endif /* MAIN_H */
