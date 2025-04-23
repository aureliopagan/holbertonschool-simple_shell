#include "main.h"

/**
 * display_prompt - Displays the shell prompt
 */
void display_prompt(void)
{
	write(STDOUT_FILENO, "#shell$ ", 7);
}

/**
 * read_input - Reads a line from stdin
 *
 * Return: input line or NULL
 */
char *read_input(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;

	read = getline(&line, &len, stdin);
	if (read == -1)
	{
		free(line);
		return (NULL);
	}

	if (line[read - 1] == '\n')
		line[read - 1] = '\0';

	return (line);
}

/**
 * parse_input - Tokenizes the input string into an array of arguments
 * @input: the command line input
 *
 * Return: pointer to array of strings (args)
 */
char **parse_input(char *input)
{
	char **args = NULL;
	char *token = NULL;
	int bufsize = 64, i = 0;

	args = malloc(sizeof(char *) * bufsize);
	if (args == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	token = strtok(input, " ");
	while (token != NULL)
	{
		args[i++] = token;
		if (i >= bufsize)
		{
			bufsize += 64;
			args = realloc(args, sizeof(char *) * bufsize);
			if (args == NULL)
			{
				perror("realloc");
				exit(EXIT_FAILURE);
			}
		}
		token = strtok(NULL, " ");
	}
	args[i] = NULL;
	return (args);
}

/**
 * free_args - Frees memory allocated for arguments
 * @args: argument array
 */
void free_args(char **args)
{
	free(args);
}

