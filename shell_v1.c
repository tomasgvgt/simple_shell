#include "holberton.h"

int main(void)
{
    char *line = NULL;
    size_t len = 0;
    int i = 1;

    while (i != -1)
    {
        printf("My_Shell$ ");
        i = getline(&line, &len, stdin);
        str_to_array((char *)line);
        free(line);
        line = NULL;
    }
    return (0);
}

int **str_to_array(char *command_line)
{
    char **token_array, *token, *tmp1 = 0;
    int i = 0, j = 0, k = 0, l = 0;

    tmp1 = strdup(command_line);
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
            token_array[j] = malloc(sizeof(char) * (strlen(token) + 1));
            if (token_array[j] == NULL)
            {
                while (k < j)
                {
                    free(token_array[k]);
                    k++;
                }
                free(token_array);
            }
            strncpy(token_array[j], token, strlen(token) + 1);
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