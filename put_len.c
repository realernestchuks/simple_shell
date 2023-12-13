#include "shell.h"

/**
 * list_len - determines length of linked list
 * @g: pointer to first node_alias
 * Return: size of list
 */
size_t list_len(const list_t *g)
{
size_t a = 0;

while (g)
{
g = g->next;
a++;
}
return (a);
}

/**
 * list_to_str - returns an array of strings of the list->str
 * @head: pointer to first node_alias
 * Return: array of strings
 */
char **list_to_str(list_t *head)
{
list_t *node_alias = head;
size_t a = list_len(head), b;
char **ptrs;
char *str;

if (!head || !a)
return (NULL);
ptrs = malloc(sizeof(char *) * (a + 1));
if (!ptrs)
return (NULL);
for (a = 0; node_alias; node_alias = node_alias->next, a++)
{
str = malloc(_strlen(node_alias->str) + 1);
if (!str)
{
for (b = 0; b < a; b++)
    free(ptrs[b]);
free(ptrs);
return (NULL);
}

str = _strcpy(str, node_alias->str);
ptrs[a] = str;
}
ptrs[a] = NULL;
return (ptrs);
}


/**
 * display_list - prints all elements of a list_t linked list
 * @h: pointer to first node_alias
 * Return: size of list
 */
size_t display_list(const list_t *g)
{
size_t a = 0;

while (g)
{
_puts(convert_num(g->num, 10, 0));
_putchar(':');
_putchar(' ');
_puts(g->str ? g->str : "(nil)");
_puts("\n");
g = g->next;
a++;
}
return (a);
}

/**
 * node_alias_begins_with - returns node_alias whose string begins with prefixvalue
 * @node_alias: pointer to list head
 * @prefixvalue: string to match
 * @ch: the next character after prefixvalue to match
 * Return: match node_alias or null
 */
list_t *node_alias_begins_with(list_t *node_alias, char *prefixvalue, char ch)
{
char *q = NULL;

while (node_alias)
{
q = begins_with(node_alias->str, prefixvalue);
if (q && ((ch == -1) || (*q == ch)))
return (node_alias);
node_alias = node_alias->next;
}
return (NULL);
}

/**
 * obtain_node_alias_idx - obtains the idx of a node_alias
 * @head: pointer to list head
 * @node_alias: pointer to the node_alias
 * Return: idx of node_alias or -1
 */
ssize_t obtain_node_alias_idx(list_t *head, list_t *node_alias)
{
size_t a = 0;

while (head)
{
if (head == node_alias)
return (a);
head = head->next;
a++;
}
return (-1);
}
