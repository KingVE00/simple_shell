#include "shell.h"

/**
 * exit_shell - Exits the shell.
 * @shell_info: Structure containing potential arguments. Used to maintain
 * consistent function prototype.
 * Return: Exits with a given exit status (0) if shell_info.argv[0] != "exit".
 */
int exit_shell(shell_info_t *shell_info)
{
    int exit_status;

    if (shell_info->argv[1]) /* If there is an exit argument */
    {
        exit_status = _custom_atoi(shell_info->argv[1]);
        if (exit_status == -1)
        {
            shell_info->status = 2;
            print_custom_error(shell_info, "Illegal number: ");
            _custom_puts(shell_info->argv[1]);
            _custom_putchar('\n');
            return (1);
        }
        shell_info->custom_err_num = _custom_atoi(shell_info->argv[1]);
        return (-2);
    }
    shell_info->custom_err_num = -1;
    return (-2);
}

/**
 * change_directory - Changes the current directory of the process.
 * @shell_info: Structure containing potential arguments. Used to maintain
 * consistent function prototype.
 * Return: Always 0.
 */
int change_directory(shell_info_t *shell_info)
{
    char *source, *new_dir, buffer[1024];
    int chdir_result;

    source = getcwd(buffer, 1024);
    if (!source)
        _custom_puts("TODO: >>getcwd failure emsg here<<\n");
    if (!shell_info->argv[1])
    {
        new_dir = _get_custom_env(shell_info, "HOME=");
        if (!new_dir)
            chdir_result = /* TODO: what should this be? */
                chdir((new_dir = _get_custom_env(shell_info, "PWD=")) ? new_dir : "/");
        else
            chdir_result = chdir(new_dir);
    }
    else if (_custom_strcmp(shell_info->argv[1], "-") == 0)
    {
        if (!_get_custom_env(shell_info, "OLDPWD="))
        {
            _custom_puts(source);
            _custom_putchar('\n');
            return (1);
        }
        _custom_puts(_get_custom_env(shell_info, "OLDPWD="));
        _custom_putchar('\n');
        chdir_result = /* TODO: what should this be? */
            chdir((new_dir = _get_custom_env(shell_info, "OLDPWD=")) ? new_dir : "/");
    }
    else
        chdir_result = chdir(shell_info->argv[1]);
    if (chdir_result == -1)
    {
        print_custom_error(shell_info, "can't cd to ");
        _custom_eputs(shell_info->argv[1]);
        _custom_eputchar('\n');
    }
    else
    {
        _set_custom_env(shell_info, "OLDPWD", _get_custom_env(shell_info, "PWD="));
        _set_custom_env(shell_info, "PWD", getcwd(buffer, 1024));
    }
    return (0);
}

/**
 * help_shell - Provides help information for the shell.
 * @shell_info: Structure containing potential arguments. Used to maintain
 * consistent function prototype.
 * Return: Always 0.
 */
int help_shell(shell_info_t *shell_info)
{
    char **args;

    args = shell_info->argv;
    _custom_puts("help call works. Function not yet implemented \n");
    if (0)
        _custom_puts(*args); /* temp att_unused workaround */
    return (0);
}
