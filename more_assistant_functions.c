#include "holberton.h"

/**
 * *_strcpy - copies a string.
 *
 * @dest: pointer to destionation string.
 * @src: pointer to source string
 *
 * Return: a char string
 */

char *_strcpy(char *dest, char *src)
{
    int i;

    for (i = 0; src[i] != '\0'; i++)
    {
        dest[i] = src[i];
    }
    dest[i] = ('\0');
    return (dest);
}

/**
 * _calloc - Allocates memory for an array of nmemb elements of size bytes.
 * @nmemb: Number of elements of the array.
 * @size: size bytes of the element type.
 * Return: Pointer to the allocated memory.
 */

void *_calloc(unsigned int nmemb, unsigned int size)
{
    char *s;
    unsigned int i;

    if (nmemb == 0 || size == 0)
        return (NULL);

    s = malloc(nmemb * size);
    if (s == NULL)
        return (NULL);

    for (i = 0; i < (size * nmemb); i++)
        s[i] = 0;
    return (s);
}

/**
 * _exit - 
 * @
 * Return: Pointer to the allocated memory.
 */

void a_exit(char **text, int i, char *command_line)
{
    int l = 0;

	while (l < i)
    {
        free(text[l]);
        l++;
    }
    free(text);
    free(command_line);
	exit(EXIT_SUCCESS);
}

/**
 * _env - 
 * @
 * Return: Pointer to the allocated memory.
 */

void _env(void)
{
    unsigned int i;

    i = 0;
    while (environ[i] != NULL)
    {
        printf("%s\n", environ[i]);
        i++;
    }
}