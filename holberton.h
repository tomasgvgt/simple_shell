#ifndef HOLBERTON_H
#define HOLBERTON_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <string.h>

#define biff_zise 1024
#define strtok_delim " \n\r\a\t"
extern char **environ;
char **str_to_array(char *command_line);
int exec_new_programm(char **command_list, int i, char *command_line);
int _strlen(char *s);
char *_strncpy(char *dest, char *src, int n);
char *_strdup(char *str);
char *_path(char *command);
char *directory(char *temporal_dir, char *command);
char *_strcat(char *dest, char *src);
char *_strdup(char *str);
int _strcmp(char *s1, char *s2);
char *_strcpy(char *dest, char *src);
void *_calloc(unsigned int nmemb, unsigned int size);
void a_exit(char **text, int i, char *command_line);
void _env(void);
void signal_handler(int signal);

#endif
