#include "holberton.h"

/**
 * main - Prints the prompt and calls all
 * the functions needed to run the shell.
 *
 * Return: Always 0.
 */

int main(void)
{
	char *line = NULL;
	size_t len = 0;
	int i = 1;

	while (i != -1)
	{
		write(STDOUT_FILENO, "My_Shell$ ", 10);
		i = getline(&line, &len, stdin);
		str_to_array((char *)line);
		free(line);
		line = NULL;
	}
	return (0);
}

/**
 * str_to_array - Takes a string and turns it into a list of strings.
 * @command_line: string.
 * Return: A list of strings.
 */

int **str_to_array(char *command_line)
{
	char **token_array, *token, *tmp1 = 0;
	int i = 0, j = 0, k = 0, l = 0;

	tmp1 = _strdup(command_line);
	token = strtok(tmp1, " \n");
	while (token != NULL)
	{
		token = strtok(NULL, " \n");
		i++;
	}
	free(tmp1);
	if (i != 0)
	{
		token_array = malloc((sizeof(char *)) * (i + 1));
		if (token_array == NULL)
			return (NULL);
		token = strtok(command_line, " \n");
		while (token != NULL)
		{
			token_array[j] = malloc(sizeof(char) * (_strlen(token) + 1));
			if (token_array[j] == NULL)
			{
				while (k < j)
					free(token_array[k]), k++;
				free(token_array);
			}
			_strncpy(token_array[j], token, _strlen(token) + 1);
			token = strtok(NULL, " \n");
			j++;
		}
		token_array[j] = NULL;
		exec_new_programm(token_array);
		while (l < i)
		{
			free(token_array[l]);
			l++;
		}
		free(token_array);
	}
	return (0);
}

/**
 * exec_new_program - Creates a child processs to start a new programm.
 * @command_list: Array of strings, each string is an agrument
 * for the programm to execute.
 * Return: 0 if success, 1 if failed.
 */

int exec_new_programm(char **command_list)
{
	char *envp[] = {NULL};
	pid_t childpid;
	int status;

	switch (childpid = fork())
	{
	case -1:
		perror("fork error");
		return (1);
	case 0:
		if (execve(command_list[0], command_list, envp) == -1)
			exit(EXIT_FAILURE);
		else
			exit(EXIT_SUCCESS);
	default:
		wait(&status);
	}
	return (0);
}
