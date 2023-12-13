#include "shell.h"

/**
 * _strcpy - copies a string
 * @destination: the destination
 * @source: the source
 * Return: pointer to destination
 */
char *_strcpy(char *destination, char *source)
{
int a = 0;

if (destination == source || source == 0)
return (destination);
while (source[a])
{
destination[a] = source[a];
a++;
}
destination[a] = 0;
return (destination);
}

/**
 * _strdup - duplicates a string
 * @str: the string to duplicate
 * Return: pointer to the duplicated string
 */
char *_strdup(const char *str)
{
int length = 0;
char *ret;

if (str == NULL)
return (NULL);
while (*str++)
length++;
ret = malloc(sizeof(char) * (length + 1));
if (!ret)
return (NULL);
for (length++; length--;)
ret[length] = *--str;
return (ret);
}

/**
 * _puts - prints an input string
 * @str: the string to be printed
 * Return: Nothing
 */
void _puts(char *str)
{
int a = 0;

if (!str)
return;
while (str[a] != '\0')
{
_putchar(str[a]);
a++;
}
}

/**
 * _putchar - writes the character c to stdout
 * @ch: The character to print
 * Return: On success 1.
 * On error, -1 is returned, and errno is put appropriately.
 */
int _putchar(char ch)
{
static int a;
static char buf[WRITE_BUF_SIZE];

if (ch == BUF_FLUSH || a >= WRITE_BUF_SIZE)
{
write(1, buf, a);
a = 0;
}
if (ch != BUF_FLUSH)
buf[a++] = ch;
return (1);
}
