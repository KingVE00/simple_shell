#include "shell.h"

/**
 * clear_info - initializes info_t struct
 * @info: struct address
 */
void clear_info(info_t *info)
{
    info->arg = NULL;
    info->argv = NULL;
    info->path = NULL;
    info->argc = 0;
}

/**
 * set_info - initializes info_t struct
 * @info: struct address
 * @av: argument vector
 */
void set_info(info_t *info, char **av)
{
    int i = 0;

    info->name = av[0];  // Modified: fname to name
    if (info->arg)
    {
        info->args = strtow(info->arg, " \t");  // Modified: argv to args
        if (!info->args)
        {
            info->args = malloc(sizeof(char *) * 2);
            if (info->args)
            {
                info->args[0] = _strdup(info->arg);
                info->args[1] = NULL;
            }
        }
        for (i = 0; info->args && info->args[i]; i++)  // Modified: argv to args
            ;
        info->arg_count = i;  // Modified: argc to arg_count

        replace_aliases(info);  // Modified: replace_alias to replace_aliases
        replace_variables(info);  // Modified: replace_vars to replace_variables
    }
}

/**
 * free_info - frees info_t struct fields
 * @info: struct address
 * @all: true if freeing all fields
 */
void free_info(info_t *info, int all)
{
    ffree(info->args);  // Modified: argv to args
    info->args = NULL;  // Modified: argv to args
    info->path = NULL;
    if (all)
    {
        if (!info->cmd_buffer)  // Modified: cmd_buf to cmd_buffer
            free(info->arg);
        if (info->environment)
            free_list(&(info->environment));  // Modified: env to environment
        if (info->history)
            free_list(&(info->history);
        if (info->aliases)
            free_list(&(info->aliases));  // Modified: alias to aliases
        ffree(info->environment_copy);  // Modified: environ to environment_copy
        info->environment_copy = NULL;  // Modified: environ to environment_copy
        bfree((void **)info->cmd_buffer);  // Modified: cmd_buf to cmd_buffer
        if (info->read_fd > 2)  // Modified: readfd to read_fd
            close(info->read_fd);  // Modified: readfd to read_fd
        _putchar(BUF_FLUSH);
    }
}
