#include "shell.h"

/**
*_myputs - Prints an input string.
*@str: The string to be printed.
*Return: Always return nothing.
*/
void _myputs(char *str)
{
int a = 0;

if (!str)
return;
while (str[a] != '\0')
{
_putchars(str[a]);
a++;
}
}

/**
*_putchars - Writes the character c to stderr.
*@ch: The character to print.
*Return: Always return on success 1.
*On error, -1 is returned, and errno is set appropriately.
*/
int _putchars(char ch)
{
static int a;
static char buf[WRITE_BUF_SIZE];

if (ch == BUF_FLUSH || a >= WRITE_BUF_SIZE)
{
write(2, buf, a);
a = 0;
}
if (ch != BUF_FLUSH)
buf[a++] = ch;
return (1);
}

/**
*_myputfd - Writes the character c to the given file descriptor (fd).
*@ch: The character to print.
*@fd: The file descriptor to write to.
*Return: Always return on success 1.
*On error, -1 is returned, and errno is set appropriately.
*/
int _myputfd(char ch, int fd)
{
static int a;
static char buf[WRITE_BUF_SIZE];

if (ch == BUF_FLUSH || a >= WRITE_BUF_SIZE)
{
write(fd, buf, a);
a = 0;
}
if (ch != BUF_FLUSH)
buf[a++] = ch;
return (1);
}

/**
*_myputsfd - Prints an input string to the given file descriptor (fd).
*@str: The string to be printed.
*@fd: The file descriptor to write to.
*Return: Always return the number of characters written.
*/
int _myputsfd(char *str, int fd)
{
int a = 0;

if (!str)
return (0);
while (*str)
{
a += _myputfd(*str++, fd);
}
return (a);
}
