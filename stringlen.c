#include "shell.h"

/**
 * _strlen - returns the length of a string
 * @str: the string whose length to check
 * Return: integer length of string
 */
int _strlen(char *str)
{
int a = 0;

if (!str)
return (0);

while (*str++)
a++;
return (a);
}

/**
 * _strcmp - performs lexicogarphic comparison of two strangs.
 * @str1: the first string
 * @str2: the second string
 * Return: negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
 */
int _strcmp(char *str1, char *str2)
{
while (*str1 && *str2)
{
if (*str1 != *str2)
return (*str1 - *str2);
str1++;
str2++;
}
if (*str1 == *str2)
return (0);
else
return (*str1 < *str2 ? -1 : 1);
}

/**
 * begins_with - checks if prefix begins with chr
 * @chr: string to search
 * @prefix: the substring to find
 * Return: address of next char of chr or NULL
 */
char *begins_with(const char *chr, const char *prefix)
{
while (*prefix)
if (*prefix++ != *chr++)
return (NULL);
return ((char *)chr);
}

/**
 * _strcat - concatenates two strings
 * @destination: the destination buffer
 * @source: the source buffer
 * Return: pointer to destination buffer
 */
char *_strcat(char *destination, char *source)
{
char *ret = destination;

while (*destination)
destination++;
while (*source)
*destination++ = *source++;
*destination = *source;
return (ret);
}
