#include "shell.h"

/**
 * **strtow - splits a string into words. Repeat delimiters are ignored
 * @str: the input string
 * @d: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **strtow(char *str, char *deli)
{
int a, b, k, m, numwords = 0;
char **s;

if (str == NULL || str[0] == 0)
return (NULL);
if (!deli)
deli = " ";
for (a = 0; str[a] != '\0'; a++)
if (!is_delimeter(str[a], deli) && (is_delimeter(str[a + 1], deli) || !str[a + 1]))
numwords++;

if (numwords == 0)
return (NULL);
s = malloc((1 + numwords) * sizeof(char *));
if (!s)
return (NULL);
for (a = 0, b = 0; b < numwords; b++)
{
while (is_delimeter(str[a], deli))
a++;
k = 0;
while (!is_delimeter(str[a + k], deli) && str[a + k])
k++;
s[b] = malloc((k + 1) * sizeof(char));
if (!s[b])
{
for (k = 0; k < b; k++)
free(s[k]);
free(s);
return (NULL);
}
for (m = 0; m < k; m++)
s[b][m] = str[a++];
s[b][m] = 0;
}
s[b] = NULL;
return (s);
}

/**
 * **strtow2 - splits a string into words
 * @str: the input string
 * @d: the delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **strtow2(char *str, char deli)
{
int a, b, k, m, numwords = 0;
char **s;

if (str == NULL || str[0] == 0)
return (NULL);
for (a = 0; str[a] != '\0'; a++)
if ((str[a] != deli && str[a + 1] == deli) ||
    (str[a] != deli && !str[a + 1]) || str[a + 1] == deli)
numwords++;
if (numwords == 0)
return (NULL);
s = malloc((1 + numwords) * sizeof(char *));
if (!s)
return (NULL);
for (a = 0, b = 0; b < numwords; b++)
{
while (str[a] == deli && str[a] != deli)
a++;
k = 0;
while (str[a + k] != deli && str[a + k] && str[a + k] != deli)
k++;
s[b] = malloc((k + 1) * sizeof(char));
if (!s[b])
{
for (k = 0; k < b; k++)
free(s[k]);
free(s);
return (NULL);
}
for (m = 0; m < k; m++)
s[b][m] = str[a++];
s[b][m] = 0;
}
s[b] = NULL;
return (s);
}
