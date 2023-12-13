#include "shell.h"

/**
*_myenviron - Prints the current environment.
*@shell: Pointer to the shell structure.
*Return: Always 0.
*/
int _myenviron(shell_t *shell)
{
print_list_string(shell->env);
return (0);
}

/**
*_obtainenv - Obtains the value of an environment variable.
*@shell: Pointer to the shell structure.
*@title: Environment variable title.
*Return: The value of the environment variable.
*/
char *_obtainenv(shell_t *shell, const char *title)
{
list_t *node_alias = shell->env;
char *q;

while (node_alias)
{
q = begins_with(node_alias->str, title);
if (q && *q)
return (q);
node_alias = node_alias->next;
}
return (NULL);
}

/**
*_myputenv - Initializes a new environment variable,
*or modifies an existing one.
*@shell: Pointer to the shell structure.
*Return: Always return 0.
*/
int _myputenv(shell_t *shell)
{
if (shell->argc != 3)
{
_myputs("Incorrect number of arguements\n");
return (1);
}
if (_putenv(shell, shell->argv[1], shell->argv[2]))
return (0);
return (1);
}

/**
*_myunputenv - Removes an environment variable.
*@shell: Pointer to the shell structure.
*Return: Always return 0.
*/
int _myunputenv(shell_t *shell)
{
int a;

if (shell->argc == 1)
{
_myputs("Too few arguements.\n");
return (1);
}
for (a = 1; a <= shell->argc; a++)
_unputenv(shell, shell->argv[a]);

return (0);
}

/**
*occupy_env_list - Occupies the environment linked list.
*@shell: Pointer to the shell structure.
*Return: Always return 0.
*/
int occupy_env_list(shell_t *shell)
{
list_t *node_alias = NULL;
size_t a;

for (a = 0; environ[a]; a++)
add_node_alias_end(&node_alias, environ[a], 0);
shell->env = node_alias;
return (0);
}
