#include "shell.h"

/**
*_strtoi - Converts a string to an integer.
*@str: The string to be converted.
*Return: Always return the converted number, 0 if no numbers in the string,
*-1 on error.
*/
int _strtoi(char *str)
{
int a = 0;
unsigned long int result = 0;

if (*str == '+')
str++;  /* TODO: why does this make main return 255? */
for (a = 0;  str[a] != '\0'; a++)
{
if (str[a] >= '0' && str[a] <= '9')
{
result *= 10;
result += (str[a] - '0');
if (result > INT_MAX)
return (-1);
}
else
return (-1);
}
return (result);
}

/**
*log_error - Prints an error message.
*@shell: Pointer to the shell structure.
*@errstring: String containing the specified error type.
*Return: It does not return a value.
*/
void log_error(shell_t *shell, char *errstring)
{
_myputs(shell->ftitle);
_myputs(": ");
print_number(shell->line_count, STDERR_FILENO);
_myputs(": ");
_myputs(shell->argv[0]);
_myputs(": ");
_myputs(errstring);
}

/**
*print_number - Prints a decimal (integer) number (base 10).
*@insert: The number to print.
*@fd: The file descriptor to write to.
*Return: Always return the number of characters printed.
*/
int print_number(int insert, int fd)
{
int (*__putchar)(char) = _putchar;
int a, count = 0;
unsigned int _abs_, current;

if (fd == STDERR_FILENO)
__putchar = _putchars;
if (insert < 0)
{
_abs_ = -insert;
__putchar('-');
count++;
}
else
_abs_ = insert;
current = _abs_;
for (a = 1000000000; a > 1; a /= 10)
{
if (_abs_ / a)
{
__putchar('0' + current / a);
count++;
}
current %= a;
}
__putchar('0' + current);
count++;

return (count);
}

/**
*convert_num - Converts a number to a string (a clone of itoa).
*@num: The number to convert.
*@base: The base for conversion.
*@labels: Argument labels.
*Return: Always return The resulting string.
*/
char *convert_num(long int num, int base, int labels)
{
static char *arr;
static char buffer[50];
char sign = 0;
char *ptr;
unsigned long n = num;

if (!(labels & CONVERT_UNSIGNED) && num < 0)
{
n = -num;
sign = '-';

}
arr = labels & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
ptr = &buffer[49];
*ptr = '\0';

do	{
*--ptr = arr[n % base];
n /= base;
} while (n != 0);

if (sign)
*--ptr = sign;
return (ptr);
}

/**
*delete_comments - Replaces the first instance of '#' with '\0'.
*@buf: Address of the string to modify.
*Return: Always return 0.
*/
void delete_comments(char *buf)
{
int a;

for (a = 0; buf[a] != '\0'; a++)
if (buf[a] == '#' && (!a || buf[a - 1] == ' '))
{
buf[a] = '\0';
break;
}
}
