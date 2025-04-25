#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
* print_environment - Prints the current environment
*/
void print_environment(void)
{
char **env = environ;

while (*env)
{
printf("%s\n", *env);
env++;
}
}

/**
* handle_builtin - Handles built-in commands
* @args: Argument vector
* Return: 1 if built-in handled, 0 otherwise
*/
int handle_builtin(char **args)
{
if (args[0] == NULL)
return (1);

if (strcmp(args[0], "exit") == 0)
{
free_args(args);
exit(0);
}
else if (strcmp(args[0], "env") == 0)
{
print_environment();
return (1);
}
else if (strcmp(args[0], "cd") == 0)
{
if (args[1] == NULL)
{
fprintf(stderr, "cd: expected argument\n");
}
else
{
if (chdir(args[1]) != 0)
perror("cd");
}
return (1);
}

return (0);
}
