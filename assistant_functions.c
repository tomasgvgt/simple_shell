#include "holberton.h"

/**
 * _strlen - Returns the lenght of a string. 
 * @s: String
 * Return: Lenght of the string. 
 */

int _strlen(char *s)
{
    int i;

    for (i = 0; s[i] != '\0'; ++i)
    {
    }

    return (i);
}

/**
 * *_strncpy - copies a string from src to dest,
 * at most, n bytes of src are copied.
 * @dest: destination string.
 * @src: source string.
 * @n: most number of bytes it will copy.
 * Return: A char string.
 */

char *_strncpy(char *dest, char *src, int n)
{

    int i;

    for (i = 0; i < n && src[i] != '\0'; i++)
        dest[i] = src[i];
    for (; i < n; i++)
        dest[i] = '\0';

    return (dest);
}

#include <stdlib.h>
#include "holberton.h"

/**
  * _strdup - Returns a pointer to a new string,
  * which is a duplicate of the string str.
  * @str: pointer string
  * Return: NULL if str = NULL or a pointer to the duplciated string
  **/

char *_strdup(char *str)
{
    int i, j;
    char *a;

    if (str == NULL)
        return (NULL);
    for (i = 0; str[i]; i++)
    {
    }
    a = malloc((i + 1) * sizeof(char));
    if (a != NULL)
    {
        for (j = 0; str[j]; j++)
            a[j] = str[j];
        a[j] = '\0';
    }
    else
        return (NULL);
    return (a);
}
