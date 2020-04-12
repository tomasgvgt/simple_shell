#ifndef HOLBERTON_H
#define HOLBERTON_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <string.h>

char **str_to_array(char *command_line);
int exec_new_programm(char **command_list);
int _strlen(char *s);
char *_strncpy(char *dest, char *src, int n);
char *_strdup(char *str);
char *_path(char *command);
char *directory(char *temporal_dir, char *command);
char *_strcat(char *dest, char *src);

#endif
