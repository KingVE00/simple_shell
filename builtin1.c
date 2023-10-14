#include "shell.h"

/**
 * _myhistory - Displays the history list with line numbers.
 * @info: Structure containing arguments and history list.
 *
 * Return: Always 0.
 */
int _myhistory(info_t *info)
{
    print_history(info->history);
    return (0);
}

/**
 * unset_alias - Unsets an alias.
 * @info: Parameter struct.
 * @str: The alias string.
 *
 * Return: 0 on success, 1 on error.
 */
int unset_alias(info_t *info, char *str)
{
    char *p, c;
    int ret;

    p = _strchr(str, '=');
    if (!p)
        return (1);
    c = *p;
    *p = 0;
    ret = delete_alias(&(info->alias), get_alias_index(info->alias, str, -1));
    *p = c;
    return (ret);
}

/**
 * set_alias - Sets an alias.
 * @info: Parameter struct.
 * @str: The alias string.
 *
 * Return: 0 on success, 1 on error.
 */
int set_alias(info_t *info, char *str)
{
    char *p;

    p = _strchr(str, '=');
    if (!p)
        return (1);
    if (!*++p)
        return (unset_alias(info, str));

    unset_alias(info, str);
    return (add_alias_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - Prints an alias string.
 * @node: The alias node.
 *
 * Return: 0 on success, 1 on error.
 */
int print_alias(list_t *node)
{
    char *p = NULL, *a = NULL;

    if (node)
    {
        p = _strchr(node->str, '=');
        for (a = node->str; a <= p; a++)
            _putchar(*a);
        _putchar('\'');
        _puts(p + 1);
        _puts("'\n");
        return (0);
    }
    return (1);
}

/**
 * _myalias - Manages alias functions.
 * @info: Structure containing arguments and alias list.
 *
 * Return: Always 0.
 */
int _myalias(info_t *info)
{
    int i = 0;
    char *p = NULL;
    list_t *node = NULL;

    if (info->argc == 1)
    {
        node = info->alias;
        while (node)
        {
            print_alias(node);
            node = node->next;
        }
        return (0);
    }
    for (i = 1; info->argv[i]; i++)
    {
        p = _strchr(info->argv[i], '=');
        if (p)
            set_alias(info, info->argv[i]);
        else
            print_alias(get_alias_starts_with(info->alias, info->argv[i], '='));
    }

    return (0);
}
