#include "shell.h"

/**
 * print_environment - prints the current environment
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int print_environment(info_t *info)
{
    print_list_str(info->env);
    return (0);
}

/**
 * find_environment - finds the value of an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 * @name: Environment variable name
 * Return: the value or NULL if not found
 */
char *find_environment(info_t *info, const char *name)
{
    list_t *node = info->env;
    char *env_value;

    while (node)
    {
        env_value = starts_with(node->str, name);
        if (env_value && *env_value)
            return env_value;
        node = node->next;
    }
    return NULL;
}

/**
 * set_environment - Initializes a new environment variable or modifies an existing one
 * @info: Structure containing potential arguments. Used to maintain constant function prototype.
 * Return: 0 on success, 1 on error
 */
int set_environment(info_t *info)
{
    if (info->argc != 3)
    {
        _eputs("Incorrect number of arguments\n");
        return 1;
    }
    if (update_environment(info, info->argv[1], info->argv[2]))
        return 0;
    return 1;
}

/**
 * unset_environment - Removes an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: 0 on success, 1 on error
 */
int unset_environment(info_t *info)
{
    int i;

    if (info->argc == 1)
    {
        _eputs("Too few arguments.\n");
        return 1;
    }

    for (i = 1; i <= info->argc; i++)
        delete_environment(info, info->argv[i]);

    return 0;
}

/**
 * initialize_environment - populates the environment linked list
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int initialize_environment(info_t *info)
{
    list_t *node = NULL;
    size_t i;

    for (i = 0; environ[i]; i++)
        add_node_end(&node, environ[i], 0);
    info->env = node;
    return 0;
}
