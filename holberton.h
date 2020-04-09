#ifndef HOLBERTON_H
#define HOLBERTON_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int **str_to_array(char *command_line);
int exec_new_programm(char **command_list);
int _strlen(char *s);
char *_strncpy(char *dest, char *src, int n);
char *_strdup(char *str);

#endif
