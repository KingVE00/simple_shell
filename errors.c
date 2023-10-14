#include "shell.h"

/**
 * print_err_string - writes an error string to stderr
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void print_err_string(char *str)
{
    int i = 0;

    if (!str)
        return;
    while (str[i] != '\0')
    {
        write_err_char(str[i]);
        i++;
    }
}

/**
 * write_err_char - writes the character c to stderr
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int write_err_char(char c)
{
    static int i;
    static char buf[WRITE_BUF_SIZE];

    if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
    {
        write(2, buf, i);
        i = 0;
    }
    if (c != BUF_FLUSH)
        buf[i++] = c;
    return (1);
}

/**
 * write_char_to_fd - writes the character c to a given file descriptor
 * @c: The character to print
 * @fd: The file descriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int write_char_to_fd(char c, int fd)
{
    static int i;
    static char buf[WRITE_BUF_SIZE];

    if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
    {
        write(fd, buf, i);
        i = 0;
    }
    if (c != BUF_FLUSH)
        buf[i++] = c;
    return (1);
}

/**
 * write_string_to_fd - writes a string to a given file descriptor
 * @str: the string to be printed
 * @fd: the file descriptor to write to
 *
 * Return: the number of characters written
 */
int write_string_to_fd(char *str, int fd)
{
    int i = 0;

    if (!str)
        return (0);
    while (*str)
    {
        i += write_char_to_fd(*str++, fd);
    }
    return (i);
}
