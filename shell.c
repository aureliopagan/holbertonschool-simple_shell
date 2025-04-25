#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

/**
* handle_child_process - Handles child process execution
* @args: Command arguments
* @full_path: Full path to command
*/
static void handle_child_process(char **args, char *full_path)
{
execve(args[0], args, environ);
perror(args[0]);
if (full_path)
{
free(full_path);
}
exit(EXIT_FAILURE);
}

/**
* handle_parent_process - Handles parent process waiting
* @full_path: Full path to command
*/
static void handle_parent_process(char *full_path)
{
wait(NULL);
if (full_path)
{
free(full_path);
}
}

/**
* execute_command - Executes external commands
* @args: Argument array
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
{
free(full_path);
}
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
* cleanup_resources - Frees allocated memory
* @args: Argument array
* @input: Input string
*/
static void cleanup_resources(char **args, char *input)
{
free_args(args);
free(input);
}

/**
* main - Entry point
* Return: 0 on success
*/
int main(void)
{
char *input = NULL;
char **args = NULL;
int interactive = isatty(STDIN_FILENO);

while (1)
{
if (interactive)
{
display_prompt();
}

input = read_input();
if (!input)
{
if (interactive)
{
write(STDOUT_FILENO, "\n", 1);
}
break;
}

args = parse_input(input);
if (args[0] && !handle_builtin(args))
{
execute_command(args);
}

cleanup_resources(args, input);
args = NULL;
input = NULL;
}
return (0);
}
