#include "shell.h"

/**
*obtain_environ - Returns the string array copy of our environ.
*@shell: Pointer to the shell structure.
*Return: Always return 0.
*/
char **obtain_environ(shell_t *shell)
{
if (!shell->environ || shell->env_changed)
{
shell->environ = list_to_str(shell->env);
shell->env_changed = 0;
}

return (shell->environ);
}

/**
*_unputenv - Removes an environment variable.
*@shell: Pointer to the shell structure.
*@var: The string environment variable property.
*Return: Always return 1 on removal, 0 otherwise.
*/
int _unputenv(shell_t *shell, char *var)
{
list_t *node_alias = shell->env;
size_t a = 0;
char *q;

if (!node_alias || !var)
return (0);

while (node_alias)
{
q = begins_with(node_alias->str, var);
if (q && *q == '=')
{
shell->env_changed = remove_node_alias_at_idx(&(shell->env), a);
a = 0;
node_alias = shell->env;
continue;
}
node_alias = node_alias->next;
a++;
}
return (shell->env_changed);
}

/**
*_putenv - Initializes a new environment variable or modifies an existing one.
*@shell: Pointer to the shell structure.
*@var: The string environment variable property.
*@value: The string environment variable value.
*Return: Always return 0.
*/
int _putenv(shell_t *shell, char *var, char *value)
{
char *buf = NULL;
list_t *node_alias;
char *q;

if (!var || !value)
return (0);

buf = malloc(_strlen(var) + _strlen(value) + 2);
if (!buf)
return (1);
_strcpy(buf, var);
_strcat(buf, "=");
_strcat(buf, value);
node_alias = shell->env;
while (node_alias)
{
q = begins_with(node_alias->str, var);
if (q && *q == '=')
{
free(node_alias->str);
node_alias->str = buf;
shell->env_changed = 1;
return (0);
}
node_alias = node_alias->next;
}
add_node_alias_end(&(shell->env), buf, 0);
free(buf);
shell->env_changed = 1;
return (0);
}
