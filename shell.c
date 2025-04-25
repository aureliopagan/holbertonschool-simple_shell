#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

/**
* handle_child_process - Handles the child process execution
* @args: Command arguments
* @full_path: Full path to command
*/
void handle_child_process(char **args, char *full_path)
{
if (execve(args[0], args, environ) == -1)
{
perror(args[0]);
if (full_path)
free(full_path);
exit(EXIT_FAILURE);
}
}

/**
* handle_parent_process - Handles the parent process waiting
* @full_path: Full path to command
*/
void handle_parent_process(char *full_path)
{
wait(NULL);
if (full_path)
free(full_path);
}

/**
* execute_command - Executes an external command using execve
* @args: Arguments (including command)
*/
void execute_command(char **args)
{
pid_t pid;
char *full_path = NULL;

if (args[0][0] != '/' && args[0][0] != '.')
{
full_path = find_path(args[0]);
if (!full_path)
{
fprintf(stderr, "%s: command not found\n", args[0]);
return;
}
args[0] = full_path;
}

pid = fork();
if (pid == -1)
{
perror("fork");
if (full_path)
free(full_path);
return;
}
else if (pid == 0)
{
handle_child_process(args, full_path);
}
else
{
handle_parent_process(full_path);
}
}

/**
* main - Entry point of the shell
* Return: Always 0
*/
int main(void)
{
char *input;
char **args;
int interactive = isatty(STDIN_FILENO);

while (1)
{
if (interactive)
display_prompt();

input = read_input();
if (!input)
{
if (interactive)
write(STDOUT_FILENO, "\n", 1);
break;
}

args = parse_input(input);
if (args[0])
{
if (!handle_builtin(args))
execute_command(args);
}

free_args(args);
free(input);
}
return (0);
}
