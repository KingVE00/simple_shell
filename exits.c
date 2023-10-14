#include "shell.h"

/**
 * _strncpy - copies a string
 * @dest: the destination string to be copied to
 * @src: the source string
 * @n: the number of characters to copy
 * 
 * Return: a pointer to the concatenated string
 */
char *_strncpy(char *dest, const char *src, size_t n)
{
    char *dest_start = dest;

    while (*src && n)
    {
        *dest = *src;
        dest++;
        src++;
        n--;
    }

    while (n)
    {
        *dest = '\0';
        dest++;
        n--;
    }

    return dest_start;
}

/**
 * _strncat - concatenates two strings
 * @dest: the first string
 * @src: the second string
 * @n: the maximum number of bytes to use
 * 
 * Return: a pointer to the concatenated string
 */
char *_strncat(char *dest, const char *src, size_t n)
{
    char *dest_start = dest;

    while (*dest)
        dest++;

    while (*src && n)
    {
        *dest = *src;
        dest++;
        src++;
        n--;
    }

    *dest = '\0';

    return dest_start;
}

/**
 * _strchr - locates a character in a string
 * @s: the string to be parsed
 * @c: the character to look for
 * 
 * Return: a pointer to the located character in the string, or NULL if not found
 */
char *_strchr(const char *s, int c)
{
    while (*s)
    {
        if (*s == c)
            return (char *)s;
        s++;
    }

    if (c == '\0')
        return (char *)s;

    return NULL;
}
