#include "shell.h"

/**
 * hsh - main shell loop
 * @shell: the parameter & return shell struct
 * @argvec: the argument vector from main()
 * Return: 0 on success, 1 on error, or error code
 */
int hsh(shell_t *shell, char **argvec)
{
ssize_t m = 0;
int builtin_result = 0;

while (m != -1 && builtin_result != -2)
{
if (interactive(shell))
_puts("$ ");
_putchars(BUF_FLUSH);
m = obtain_input(shell);
if (m != -1)
{
put_shell(shell, argvec);
builtin_result = locate_builtin(shell);
if (builtin_result == -1)
locate_command(shell);
}
else if (interactive(shell))
_putchar('\n');
free_shell(shell, 0);
}
write_record(shell);
free_shell(shell, 1);
if (!interactive(shell) && shell->status)
exit(shell->status);
if (builtin_result == -2)
{
if (shell->err_num == -1)
exit(shell->status);
exit(shell->err_num);
}
return (builtin_result);
}

/**
 * locate_builtin - finds a builtin command
 * @shell: the parameter & return shell struct
 * Return: -1 if builtin not found,
 * 	0 if builtin executed successfully,
 * 	1 if builtin found but not successful,
 * 	2 if builtin signals exit()
 */
int locate_builtin(shell_t *shell)
{
int a, built_in_ret = -1;
builtin_table builtintbl[] = {
{"exit", exit_shell},
{"env", _myenviron},
{"help", _process},
{"record", record_list},
{"putenv", _myputenv},
{"unputenv", _myunputenv},
{"cd", _cd},
{"alias", handle_alias},
{NULL, NULL}
};

for (a = 0; builtintbl[a].type; a++)
if (_strcmp(shell->argv[0], builtintbl[a].type) == 0)
{
shell->line_count++;
built_in_ret = builtintbl[a].func(shell);
break;
}
return (built_in_ret);
}

/**
 * locate_command - finds a command in PATH
 * @shell: the parameter & return shell struct
 * Return: void
 */
void locate_command(shell_t *shell)
{
char *path = NULL;
int a, k;

shell->path = shell->argv[0];

if (shell->totallines_label == 1)
{
shell->line_count++;
shell->totallines_label = 0;
}

for (a = 0, k = 0; shell->arg[a]; a++)
{
if (!is_delimeter(shell->arg[a], " \t\n"))
k++;
}

if (!k)
return;

path = search_path(shell, _obtainenv(shell, "PATH="), shell->argv[0]);

if (path)
{
shell->path = path;
fork_command(shell);
}
else
{
if ((interactive(shell) || _obtainenv(shell, "PATH=") || shell->argv[0][0] == '/') && _mycmd(shell, shell->argv[0]))
fork_command(shell);
else if (*(shell->arg) != '\n')
{
shell->status = 127;
log_error(shell, "not found\n");
}
}
}

/**
 * fork_command - forks a an exec thread to run cmd
 * @shell: the parameter & return shell struct
 * Return: void
 */
void fork_command(shell_t *shell)
{
pid_t child_pid;

child_pid = fork();
if (child_pid == -1)
{
/* TODO: PUT ERROR FUNCTION */
perror("Error:");
return;
}
if (child_pid == 0)
{
if (execve(shell->path, shell->argv, obtain_environ(shell)) == -1)
{
free_shell(shell, 1);
if (errno == EACCES)
exit(126);
exit(1);
}
/* TODO: PUT ERROR FUNCTION */
}
else
{
wait(&(shell->status));
if (WIFEXITED(shell->status))
{
shell->status = WEXITSTATUS(shell->status);
if (shell->status == 126)
log_error(shell, "Permission denied\n");
}
}
}
