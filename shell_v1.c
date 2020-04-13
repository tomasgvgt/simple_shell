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
		write(STDOUT_FILENO, "My_Shell$ ", 10);
		i = getline(&line, &len, stdin);
		str_to_array(line);
		free(line);
		line = NULL;
	}
	write(STDOUT_FILENO, "\n", 1);
	return (0);
}

/**
 * str_to_array - Takes a string and turns it into a list of strings.
 * @command_line: string.
 * Return: A list of strings.
 */

char **str_to_array(char *command_line)
{
	char **token_array, *token, *tmp = 0;
	int i = 0, j = 0, k = 0, l = 0;

	tmp = strdup(command_line);
	token = strtok(tmp, " \n");
	while (token != NULL)
	{
		token = strtok(NULL, " \n");
		i++;
	}
	free(tmp);
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
	pid_t childpid;
	int status;
	struct stat st;
	char *directory, *not_command = {"it isn't a command"};

	switch (childpid = fork())
	{
	case -1:
		perror("fork error");
		return (1);
	case 0:
		if  (stat(command_list[0], &st) == 0 && st.st_mode & S_IXUSR)
        {
            if (execve(command_list[0], command_list, environ) == -1)
            {
                perror("My_Shell$ Error");
                exit(EXIT_FAILURE);
		    }
            else
                exit(EXIT_SUCCESS);
        }
        else
        {
            directory = _path(command_list[0]);
			if (strcmp(directory, not_command) == 0)
			{
                perror("My_Shell$ Error");
                exit(EXIT_FAILURE);
			}
			else
			{
				if (execve(directory, command_list, environ) == -1)
				{
					free(directory);
					perror("My_Shell$ Error");
					exit(EXIT_FAILURE);
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
        env = strdup(environ[i]);
        token = strtok(env, "=");
        if (strcmp(token, var) == 0)
        {
            token = strtok(NULL, "=");
            dir_temp = strdup(token);
            path = directory(dir_temp, command);
            free(dir_temp);
        }
        free(env);
        i++;
    }
    return(path);
}

char *directory(char *temporal_dir, char *command)
{
    char *path, *token, slash[] = {'/'}, flag = 0, *not_command = {"it isn't a command"};
    struct stat st;

	token = strtok(temporal_dir, ":");
	while (token != NULL)
	{
        path = malloc(_strlen(token) + 1 + _strlen(command) + 1);
        strcpy(path, token);
		strcat(path, slash);
		strcat(path, command);
        if  (stat(path, &st) == 0 && st.st_mode & S_IXUSR)
		{
			flag++;
			break;
		}
		token = strtok(NULL, ":");
        free(path);  
	}
	if (flag == 1)
		return(path);
	else
		return(not_command);
}
