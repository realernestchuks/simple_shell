#include "shell.h"

/**
*reset_shell - Initializes the shell_t struct.
*@shell: Pointer to the shell structure.
*/
void reset_shell(shell_t *shell)
{
shell->arg = NULL;
shell->argv = NULL;
shell->path = NULL;
shell->argc = 0;
}

/**
*put_shell - Initializes the shell_t struct with the given argument vector.
*@shell: Pointer to the shell structure.
*@argvec: Argument vector for initialization.
*/
void put_shell(shell_t *shell, char **argvec)
{
int a = 0;

shell->ftitle = argvec[0];
if (shell->arg)
{
shell->argv = strtow(shell->arg, " \t");
if (!shell->argv)
{
shell->argv = malloc(sizeof(char *) * 2);
if (shell->argv)
{
shell->argv[0] = _strdup(shell->arg);
shell->argv[1] = NULL;
}
}
for (a = 0; shell->argv && shell->argv[a]; a++)
;
shell->argc = a;

reinstate_alias(shell);
reinstate_vars(shell);
}
}

/**
*free_shell - Frees the shell_t struct fields.
*@shell: Pointer to the shell structure.
*@all: True if freeing all fields.
*/
void free_shell(shell_t *shell, int all)
{
release_memory(shell->argv);
shell->argv = NULL;
shell->path = NULL;
if (all)
{
if (!shell->cmd_buf)
free(shell->arg);
if (shell->env)
cleanup_list(&(shell->env));
if (shell->record)
cleanup_list(&(shell->record));
if (shell->alias)
cleanup_list(&(shell->alias));
release_memory(shell->environ);
shell->environ = NULL;
bfree((void **)shell->cmd_buf);
if (shell->readfd > 2)
close(shell->readfd);
_putchar(BUF_FLUSH);
}
}
