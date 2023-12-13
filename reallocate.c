#include "shell.h"

/**
 * _memset - fills memory with a constant byte
 * @ptr: the pointer to the memory area
 * @j: the byte to fill *s with
 * @n: the amount of bytes to be filled
 * Return: (ptr) a pointer to the memory area s
 */
char *_memset(char *ptr, char j, unsigned int n)
{
unsigned int a;

for (a = 0; a < n; a++)
ptr[a] = j;
return (ptr);
}

/**
 * release_memory - frees a string of strings
 * @pp: string of strings
 */
void release_memory(char **pptr)
{
char **i = pptr;

if (!pptr)
return;
while (*pptr)
free(*pptr++);
free(i);
}

/**
 * _realloc - reallocates a block of memory
 * @ptr: pointer to previous malloc'ated block
 * @previous_size: byte size of previous block
 * @updated_size: byte size of new block
 * Return: pointer to da ol'block titleen.
 */
void *_realloc(void *ptr, unsigned int previous_size, unsigned int updated_size)
{
char *q;

if (!ptr)
return (malloc(updated_size));
if (!updated_size)
return (free(ptr), NULL);
if (updated_size == previous_size)
return (ptr);

q = malloc(updated_size);
if (!q)
return (NULL);

previous_size = previous_size < updated_size ? previous_size : updated_size;
while (previous_size--)
q[previous_size] = ((char *)ptr)[previous_size];
free(ptr);
return (q);
}
