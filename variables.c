#include "shell.h"

/**
 * validate_chain - test if current char in buffer is a chain delimeter
 * @shell: the parameter struct
 * @buf: the char buffer
 * @q: address of current position in buf
 * Return: 1 if chain delimeter, 0 otherwise
 */
int validate_chain(shell_t *shell, char *buf, size_t *q)
{
size_t b = *q;

if (buf[b] == '|' && buf[b + 1] == '|')
{
buf[b] = 0;
b++;
shell->cmd_buf_type = CMD_OR;
}
else if (buf[b] == '&' && buf[b + 1] == '&')
{
buf[b] = 0;
b++;
shell->cmd_buf_type = CMD_AND;
}
else if (buf[b] == ';') /* found end of this command */
{
buf[b] = 0; /* replace semicolon with null */
shell->cmd_buf_type = CMD_CHAIN;
}
else
return (0);
*q = b;
return (1);
}

/**
 * target_chain - checks we should continue chaining based on last status
 * @shell: the parameter struct
 * @buf: the char buffer
 * @q: address of current position in buf
 * @a: starting position in buf
 * @len: length of buf
 *
 * Return: Void
 */
void target_chain(shell_t *shell, char *buf, size_t *q, size_t a, size_t len)
{
size_t b = *q;

if (shell->cmd_buf_type == CMD_AND)
{
if (shell->status)
{
buf[a] = 0;
b = len;
}
}
if (shell->cmd_buf_type == CMD_OR)
{
if (!shell->status)
{
buf[a] = 0;
b = len;
}
}

*q = b;
}

/**
 * reinstate_alias - replaces an aliases in the tokenized string
 * @shell: the parameter struct
 * Return: 1 if replaced, 0 otherwise
 */
int reinstate_alias(shell_t *shell)
{
int a;
list_t *node_alias;
char *q;

for (a = 0; a < 10; a++)
{
node_alias = node_alias_begins_with(shell->alias, shell->argv[0], '=');
if (!node_alias)
return (0);
free(shell->argv[0]);
q = _strchr(node_alias->str, '=');
if (!q)
return (0);
q = _strdup(q + 1);
if (!q)
return (0);
shell->argv[0] = q;
}
return (1);
}

/**
 * reinstate_vars - replaces vars in the tokenized string
 * @shell: the parameter struct
 * Return: 1 if replaced, 0 otherwise
 */
int reinstate_vars(shell_t *shell)
{
int a = 0;
list_t *node_alias;

for (a = 0; shell->argv[a]; a++)
{
if (shell->argv[a][0] != '$' || !shell->argv[a][1])
continue;

if (!_strcmp(shell->argv[a], "$?"))
{
replace_string(&(shell->argv[a]),
_strdup(convert_num(shell->status, 10, 0)));
continue;
}
if (!_strcmp(shell->argv[a], "$$"))
{
replace_string(&(shell->argv[a]),
_strdup(convert_num(getpid(), 10, 0)));
continue;
}
node_alias = node_alias_begins_with(shell->env, &shell->argv[a][1], '=');
if (node_alias)
{
replace_string(&(shell->argv[a]),
_strdup(_strchr(node_alias->str, '=') + 1));
continue;
}
replace_string(&shell->argv[a], _strdup(""));

}
return (0);
}

/**
 * replace_string - replaces string
 * @previous: address of previous string
 * @modified: modified string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_string(char **previous, char *modified)
{
free(*previous);
*previous = modified;
return (1);
}
