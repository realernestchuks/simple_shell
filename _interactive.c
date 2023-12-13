#include "shell.h"

/**
*interactive - returns true if shell is interactive mode
*@shell: pointer to the shell structure
*Return: Always return 1 if interactive mode, 0 otherwise
*/
int interactive(shell_t *shell)
{
return (isatty(STDIN_FILENO) && shell->readfd <= 2);
}

/**
*is_delimeter - Checks if a character is a delimiter.
*@ch: The character to check.
*@delimiter: The delimiter string.
*Return: Always return 1 if true, 0 if false.
*/
int is_delimeter(char ch, char *delimeter)
{
while (*delimeter)
if (*delimeter++ == ch)
return (1);
return (0);
}

/**
*_isalpha - Checks if a character is alphabetic.
*@ch: The character to check.
*Return: Always return 1 if @ch is alphabetic, 0 otherwise.
*/
int _isalpha(int ch)
{
if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
return (1);
else
return (0);
}

/**
*_atoi - Converts a string to an integer.
*@str: The string to be converted.
*Return: The converted number, or 0 if no numbers in the string.
*/
int _atoi(char *str)
{
int a, sign = 1, flag = 0, output;
unsigned int result = 0;

for (a = 0; str[a] != '\0' && flag != 2; a++)
{
if (str[a] == '-')
sign *= -1;

if (str[a] >= '0' && str[a] <= '9')
{
flag = 1;
result *= 10;
result += (str[a] - '0');
}
else if (flag == 1)
flag = 2;
}
if (sign == -1)
output = -result;
else
output = result;
return (output);
}
