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