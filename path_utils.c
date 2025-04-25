#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

/**
* build_full_path - Constructs full path from directory and command
* @dir: Directory path
* @cmd: Command name
* Return: Allocated full path string
*/
char *build_full_path(char *dir, char *cmd)
{
char *full_path;
int dir_len = strlen(dir);
int cmd_len = strlen(cmd);

full_path = malloc(dir_len + cmd_len + 2);
if (!full_path)
return (NULL);

strcpy(full_path, dir);
strcat(full_path, "/");
strcat(full_path, cmd);

return (full_path);
}

/**
* check_command_access - Checks if command exists and is executable
* @full_path: Path to check
* Return: 1 if accessible, 0 otherwise
*/
int check_command_access(char *full_path)
{
struct stat st;

if (stat(full_path, &st) == 0 && (st.st_mode & S_IXUSR))
return (1);
return (0);
}

/**
* find_path - Locates a command in PATH
* @cmd: Command to find
* Return: Full path if found, NULL otherwise
*/
char *find_path(char *cmd)
{
char *path = getenv("PATH");
char *path_copy, *dir, *full_path = NULL;

if (!path || !cmd)
return (NULL);

path_copy = strdup(path);
if (!path_copy)
return (NULL);

dir = strtok(path_copy, ":");
while (dir)
{
full_path = build_full_path(dir, cmd);
if (full_path)
{
if (check_command_access(full_path))
{
free(path_copy);
return (full_path);
}
free(full_path);
}
dir = strtok(NULL, ":");
}

free(path_copy);
return (NULL);
}
