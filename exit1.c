#include "shell.h"
char *strchr(const char *__str, int __ch);
/**
*record_list - displays the record list, one command by line, preceded
*with line numbers, starting at 0.
*@shell: Structure containing potential arguments. Used to maintain
*constant function prototype.
*Return: Always return 0
*/
int record_list(shell_t *shell)
{
display_list(shell->record);
return (0);
}

/**
*remove_alias - puts alias to string
*@shell: parameter struct
*@str: the string alias
*Return: Always return 0 on success, 1 on error
*/
int remove_alias(shell_t *shell, char *str)
{
char *q, ch;
int ret;

q = _strchr(str, '=');
if (!q)
return (1);
ch = *q;
*q = 0;
ret = remove_node_alias_at_idx(&(shell->alias),
obtain_node_alias_idx(shell->alias, node_alias_begins_with(shell->alias, str, -1)));
*q = ch;
return (ret);
}

/**
*put_alias - puts alias to string
*@shell: parameter struct
*@str: the string alias
*Return: Always return 0 on success, 1 on error
*/
int put_alias(shell_t *shell, char *str)
{
char *q;

q = _strchr(str, '=');
if (!q)
return (1);
if (!*++q)
return (remove_alias(shell, str));

remove_alias(shell, str);
return (add_node_alias_end(&(shell->alias), str, 0) == NULL);
}

/**
*print_alias - Prints an alias string.
*@node_alias: The alias node.
*Return: Always return 0 on success, 1 on error.
*/
int print_alias(list_t *node_alias)
{
char *q = NULL, *i = NULL;

if (node_alias)
{
q = _strchr(node_alias->str, '=');
for (i = node_alias->str; i <= q; i++)
_putchar(*i);
_putchar('\'');
_puts(q + 1);
_puts("'\n");
return (0);
}
return (1);
}

/**
*handle_alias - Implements the alias builtin (man alias).
*@shell: Pointer to the shell structure.
*Return: Always return 0.
*/
int handle_alias(shell_t *shell)
{
int a = 0;
char *q = NULL;
list_t *node_alias = NULL;

if (shell->argc == 1)
{
node_alias = shell->alias;
while (node_alias)
{
print_alias(node_alias);
node_alias = node_alias->next;
}
return (0);
}
for (a = 1; shell->argv[a]; a++)
{
q = _strchr(shell->argv[a], '=');
if (q)
put_alias(shell, shell->argv[a]);
else
print_alias(node_alias_begins_with(shell->alias, shell->argv[a], '='));
}

return (0);
}
