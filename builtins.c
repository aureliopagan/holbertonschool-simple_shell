#include "main.h"
#include <stdlib.h>

/**
 * handle_builtin - Handles built-in commands like cd and exit
 * @args: argument vector
 *
 * Return: 1 if built-in was handled, 0 otherwise
 */
int handle_builtin(char **args)
{
    if (args[0] == NULL)
        return (1);

    if (strcmp(args[0], "exit") == 0)
    {
        /* Free any allocated memory here */
        free_args(args);  /* Free the argument array */
        exit(0);         /* Exit with status 0 */
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
