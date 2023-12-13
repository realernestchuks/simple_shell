#include "shell.h"

/**
*exit_shell - Exits the shell.
*@shell: Pointer to the shell structure.
*Return: Exits with a given exit status (0) if shell.argv[0] != "exit".
*/
int exit_shell(shell_t *shell)
{
int exit_check;

if (shell->argv[1]) /* If there is an exit arguement */
{
exit_check = _strtoi(shell->argv[1]);
if (exit_check == -1)
{
shell->status = 2;
log_error(shell, "Illegal number: ");
_myputs(shell->argv[1]);
_putchars('\n');
return (1);
}
shell->err_num = _strtoi(shell->argv[1]);
return (-2);
}
shell->err_num = -1;
return (-2);
}

/**
*_cd - Changes the current directory of the process.
*@shell: Pointer to the shell structure.
*Return: Always 0.
*/
int _cd(shell_t *shell)
{
char *str, *dir, buffer[1024];
int chdir_return;

str = getcwd(buffer, 1024);
if (!str)
_puts("TODO: >>getcwd failure emsg here<<\n");
if (!shell->argv[1])
{
dir = _obtainenv(shell, "HOME=");
if (!dir)
chdir_return = /* TODO: what should this be? */
chdir((dir = _obtainenv(shell, "PWD=")) ? dir : "/");
else
chdir_return = chdir(dir);
}
else if (_strcmp(shell->argv[1], "-") == 0)
{
if (!_obtainenv(shell, "OLDPWD="))
{
_puts(str);
_putchar('\n');
return (1);
}
_puts(_obtainenv(shell, "OLDPWD=")), _putchar('\n');
chdir_return = /* TODO: what should this be? */
chdir((dir = _obtainenv(shell, "OLDPWD=")) ? dir : "/");
}
else
chdir_return = chdir(shell->argv[1]);
if (chdir_return == -1)
{
log_error(shell, "can't cd to ");
_myputs(shell->argv[1]), _putchars('\n');
}
else
{
_putenv(shell, "OLDPWD", _obtainenv(shell, "PWD="));
_putenv(shell, "PWD", getcwd(buffer, 1024));
}
return (0);
}

/**
*_change_directory - Changes the current directory of the process.
*@shell: Pointer to the shell structure.
*Return: Always 0.
*/
int _process(shell_t *shell)
{
char **arg_arr;

arg_arr = shell->argv;
_puts("help call works. Function not yet implemented \n");
if (0)
_puts(*arg_arr); /* temp att_unused workaround */
return (0);
}
