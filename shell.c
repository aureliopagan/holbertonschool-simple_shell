#include "main.h"

/**
 * execute_command - Executes external command using execvp
 * @args: arguments (including command)
 */
void execute_command(char **args)
{
	pid_t pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return;
	}
	else if (pid == 0)
	{
		if (execvp(args[0], args) == -1)
		{
			perror("./shell");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		wait(NULL);
	}
}

/**
 * main - Entry point of the shell
 *
 * Return: Always 0
 */
int main(void)
{
	char *input;
	char **args;

	while (1)
	{
		display_prompt();
		input = read_input();

		if (input == NULL)
		{
			write(STDOUT_FILENO, "\n", 1);
			break;
		}

		args = parse_input(input);

		if (args[0] != NULL)
		{
			if (!handle_builtin(args))
				execute_command(args);
		}

		free_args(args);
		free(input);
	}
	return (0);
}

