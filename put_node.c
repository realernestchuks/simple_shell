#include "shell.h"

/**
 * add_node_alias - adds a node_alias to the start of the list
 * @head: address of pointer to head node_alias
 * @str: str field of node_alias
 * @num: node_alias idx used by record
 * Return: size of list
 */
list_t *add_node_alias(list_t **head, const char *str, int num)
{
list_t *new_head;

if (!head)
return (NULL);
new_head = malloc(sizeof(list_t));
if (!new_head)
return (NULL);
_memset((void *)new_head, 0, sizeof(list_t));
new_head->num = num;
if (str)
{
new_head->str = _strdup(str);
if (!new_head->str)
{
free(new_head);
return (NULL);
}
}
new_head->next = *head;
*head = new_head;
return (new_head);
}

/**
 * add_node_alias_end - adds a node_alias to the end of the list
 * @head: address of pointer to head node_alias
 * @str: str field of node_alias
 * @num: node_alias idx used by record
 * Return: size of list
 */
list_t *add_node_alias_end(list_t **head, const char *str, int num)
{
list_t *new_node_alias, *node_alias;

if (!head)
return (NULL);

node_alias = *head;
new_node_alias = malloc(sizeof(list_t));
if (!new_node_alias)
return (NULL);
_memset((void *)new_node_alias, 0, sizeof(list_t));
new_node_alias->num = num;
if (str)
{
new_node_alias->str = _strdup(str);
if (!new_node_alias->str)
{
free(new_node_alias);
return (NULL);
}
}
if (node_alias)
{
while (node_alias->next)
node_alias = node_alias->next;
node_alias->next = new_node_alias;
}
else
*head = new_node_alias;
return (new_node_alias);
}

/**
 * print_list_string - prints only the str element of a list_t linked list
 * @g: pointer to first node_alias
 * Return: size of list
 */
size_t print_list_string(const list_t *g)
{
size_t a = 0;

while (g)
{
_puts(g->str ? g->str : "(nil)");
_puts("\n");
g = g->next;
a++;
}
return (a);
}

/**
 * remove_node_alias_at_idx - removes node_alias at given idx
 * @head: address of pointer to first node_alias
 * @idx: idx of node_alias to remove
 * Return: 1 on success, 0 on failure
 */
int remove_node_alias_at_idx(list_t **head, unsigned int idx)
{
list_t *node_alias, *last_node_alias;
unsigned int a = 0;

if (!head || !*head)
return (0);

if (!idx)
{
node_alias = *head;
*head = (*head)->next;
free(node_alias->str);
free(node_alias);
return (1);
}
node_alias = *head;
while (node_alias)
{
if (a == idx)
{
last_node_alias->next = node_alias->next;
free(node_alias->str);
free(node_alias);
return (1);
}
a++;
last_node_alias = node_alias;
node_alias = node_alias->next;
}
return (0);
}

/**
 * cleanup_list - frees all node_aliass of a list
 * @head_ptr: address of pointer to head node_alias
 * Return: void
 */
void cleanup_list(list_t **head_ptr)
{
list_t *node_alias, *next_node_alias, *head;

if (!head_ptr || !*head_ptr)
return;
head = *head_ptr;
node_alias = head;
while (node_alias)
{
next_node_alias = node_alias->next;
free(node_alias->str);
free(node_alias);
node_alias = next_node_alias;
}
*head_ptr = NULL;
}
