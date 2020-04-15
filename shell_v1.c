#include "holberton.h"

/**
 * main - Prints the prompt and calls all
 * the functions needed to run the shell.
 * Return: Always 0.
 */

int main(void)
{
	char *line = NULL;
	size_t len = 0;
	int i = 1;

	while (i != -1)
	{
		signal(SIGINT, signal_handler);
		if (isatty(STDIN_FILENO) == 1)
			write(STDOUT_FILENO, "My_Shell$ ", 10);
		i = getline(&line, &len, stdin);
		str_to_array(line);
		free(line);
		line = NULL;
	}
	/*write(STDOUT_FILENO, "\n", 1);*/
	return (0);
}

/**
 * str_to_array - Takes a string and turns it into a list of strings.
 * @command_line: string.
 * Return: A list of strings.
 */

char **str_to_array(char *command_line)
{
	char **token_array, *token, *tmp = 0, *exit = {"exit"}, *envi = {"env"};
	int i = 0, j = 0, k = 0, l = 0;

	tmp = _strdup(command_line);
	token = strtok(tmp, strtok_delim);
	while (token != NULL)
	{
		token = strtok(NULL, strtok_delim);
		i++;
	}
	free(tmp);
	if (i != 0)
	{
		/*token_array = malloc((sizeof(char *)) * (i + 1));*/
		token_array = _calloc((i + 1), (sizeof(char *)));
		if (token_array == NULL)
			return (NULL);
		token = strtok(command_line, strtok_delim);
		while (token != NULL)
		{
			/*token_array[j] = malloc(sizeof(char) * (_strlen(token) + 1));*/
			token_array[j] = _calloc((_strlen(token) + 1), sizeof(char));
			if (token_array[j] == NULL)
			{
				while (k < j)
					free(token_array[k]), k++;
				free(token_array);
			}
			_strncpy(token_array[j], token, _strlen(token) + 1);
			token = strtok(NULL, strtok_delim);
			j++;
		}
		token_array[j] = NULL;
		if (_strcmp(token_array[0], exit) == 0)
			a_exit(token_array, i, command_line);
		if (_strcmp(token_array[0], envi) == 0)
			_env();
		exec_new_programm(token_array, i, command_line);
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

int exec_new_programm(char **command_list, int i, char *command_line)
{
	pid_t childpid;
	int status, l = 0;
	struct stat st;
	char *directory, *not_command = {"it isn't a command"};

	switch (childpid = fork())
	{
	case -1:
		perror("fork error");
		return (1);
	case 0:
		if (stat(command_list[0], &st) == 0 && st.st_mode & S_IXUSR)
		{
			if (execve(command_list[0], command_list, environ) == -1)
			{
				perror("My_Shell$ Error");
				/*exit(EXIT_FAILURE);*/
				return (0);
			}
			else
				exit(EXIT_SUCCESS);
		}
		else
		{
			directory = _path(command_list[0]);
			if (_strcmp(directory, not_command) == 0)
			{
				while (l < i)
				{
					free(command_list[l]);
					l++;
				}
				free(command_list);
				free(command_line);
				perror("My_Shell$");
				exit(EXIT_FAILURE);
			}
			else
			{
				if (execve(directory, command_list, environ) == -1)
				{
					free(directory);
					perror("My_Shell$ Error");
					/* exit(EXIT_FAILURE); */
					return (0);
				}
				else
					exit(EXIT_SUCCESS);
			}
		}
	default:
		wait(&status);
	}
	return (0);
}

char *_path(char *command)
{
	int i = 0;
	char var[] = "PATH", *path, *token, *env, *dir_temp;

	while (environ[i])
	{
		env = _strdup(environ[i]);
		token = strtok(env, "=");
		if (_strcmp(token, var) == 0)
		{
			token = strtok(NULL, "=");
			dir_temp = _strdup(token);
			path = directory(dir_temp, command);
			free(dir_temp);
		}
		free(env);
		i++;
	}
	return (path);
}

char *directory(char *temporal_dir, char *command)
{
	char *path, *token, slash[] = {'/'}, flag = 0, *not_command = {"it isn't a command"};
	struct stat st;

	token = strtok(temporal_dir, ":");
	while (token != NULL)
	{
		/*path = malloc(_strlen(token) + 1 + _strlen(command) + 1);*/
		path = _calloc(_strlen(token) + _strlen(command) + 2, sizeof(char));
		_strcpy(path, token);
		_strcat(path, slash);
		_strcat(path, command);
		if (stat(path, &st) == 0 && st.st_mode & S_IXUSR)
		{
			flag++;
			break;
		}
		token = strtok(NULL, ":");
		free(path);
	}
	if (flag == 1)
		return (path);
	else
		return (not_command);
}
