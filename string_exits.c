#include "shell.h"

/**
*_strncpy - Copies a string.
*@destination: The destination string to be copied to.
*@source: The source string.
*@n: The number of characters to be copied.
*Return: Always return the concatenated string.
*/
char *_strncpy(char *destination, char *source, int n)
{
int a, b;
char *s = destination;

a = 0;
while (source[a] != '\0' && a < n - 1)
{
destination[a] = source[a];
a++;
}
if (a < n)
{
b = a;
while (b < n)
{
destination[b] = '\0';
b++;
}
}
return (s);
}

/**
*_strncat - Concatenates two strings.
*@destination: The first string.
*@source: The second string.
*@n: The maximum number of bytes to be used.
*Return: Always return the concatenated string.
*/
char *_strncat(char *destination, char *source, int n)
{
int a, b;
char *s = destination;

a = 0;
b= 0;
while (destination[a] != '\0')
a++;
while (source[b] != '\0' && b < n)
{
destination[a] = source[b];
a++;
b++;
}
if (b < n)
destination[a] = '\0';
return (s);
}

/**
*_strchr - Locates a character in a string.
*@s: The string to be parsed.
*@c: The character to look for.
*Return: Always return  pointer to the memory area in s containing the character.
*/
char *_strchr(char *s, char c)
{
do {
if (*s == c)
return (s);
} while (*s++ != '\0');

return (NULL);
}
