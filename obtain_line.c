#include "shell.h"
char *_strcat(char *destination, char *source);
char *_strcpy(char *destination, char *source);
/**
*insert_buf - Buffers chained commands.
*@shell: Pointer to the parameter struct.
*@buf: Address of the buffer.
*@len: Address of the len variable.
*Return: The number of bytes read.
*/
ssize_t insert_buf(shell_t *shell, char **buf, size_t *len)
{
ssize_t m = 0;
size_t strlength = 0;

if (!*len) /* if nothing left in the buffer, fill it */
{
/*bfree((void **)shell->cmd_buf);*/
free(*buf);
*buf = NULL;
signal(SIGINT, sigintHandler);
#if USE_OBTAINLINE
m = obtainline(buf, &strlength, stdin);
#else
m = _obtainline(shell, buf, &strlength);
#endif
if (m > 0)
{
if ((*buf)[m - 1] == '\n')
{
(*buf)[m - 1] = '\0'; /* remove trailing newline */
m--;
}
shell->totallines_label = 1;
delete_comments(*buf);
build_record_list(shell, *buf, shell->reccount++);
/* if (_strchr(*buf, ';')) is this a command chain? */
{
*len = m;
shell->cmd_buf = buf;
}
}
}
return (m);
}

/**
 * obtain_input - obtains a line minus the newline
 * @shell: parameter struct
 *
 * Return: bytes read
 */
ssize_t obtain_input(shell_t *shell)
{
static char *buf; /* the ';' command chain buffer */
static size_t a, b, len;
ssize_t m = 0;
char **buf_p = &(shell->arg), *q;

_putchar(BUF_FLUSH);
m = insert_buf(shell, &buf, &len);
if (m == -1) /* EOF */
return (-1);
if (len) /* we have commands left in the chain buffer */
{
b = a; /* init new iterator to current buf position */
q = buf + a; /* obtain pointer for return */

target_chain(shell, buf, &b, a, len);
while (b < len) /* iterate to semicolon or end */
{
if (validate_chain(shell, buf, &b))
break;
b++;
}

a = b + 1; /* increment past nulled ';'' */
if (a >= len) /* reached end of buffer? */
{
a = len = 0; /* reput position and length */
shell->cmd_buf_type = CMD_NORM;
}

*buf_p = q; /* pass back pointer to current command position */
return (_strlen(q)); /* return length of current command */
}

*buf_p = buf; /* else not a chain, pass back buffer from _obtainline() */
return (m); /* return length of buffer from _obtainline() */
}

/**
 * read_buf - reads a buffer
 * @shell: parameter struct
 * @buf: buffer
 * @a: size
 *
 * Return: r
 */
ssize_t read_buf(shell_t *shell, char *buf, size_t *a)
{
ssize_t m = 0;

if (*a)
return (0);
m = read(shell->readfd, buf, READ_BUF_SIZE);
if (m >= 0)
*a = m;
return (m);
}

/**
 * _obtainline - obtains the next line of input from STDIN
 * @shell: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int _obtainline(shell_t *shell, char **ptr, size_t *length)
{
static char buf[READ_BUF_SIZE];
static size_t a, len;
size_t k;
ssize_t m = 0, s = 0;
char *q = NULL, *new_p = NULL, *ch;

q = *ptr;
if (q && length)
s = *length;
if (a == len)
a = len = 0;

m = read_buf(shell, buf, &len);
if (m == -1 || (m == 0 && len == 0))
return (-1);

ch = _strchr(buf + a, '\n');
k = ch ? 1 + (unsigned int)(ch - buf) : len;
new_p = _realloc(q, s, s ? s + k : k + 1);
if (!new_p) /* MALLOC FAILURE! */
return (q ? free(q), -1 : -1);

if (s)
_strncat(new_p, buf + a, k - a);
else
_strncpy(new_p, buf + a, k - a + 1);

s += k - a;
a = k;
q = new_p;

if (length)
*length = s;
*ptr = q;
return (s);
}

/**
 * sigintHandler - blocks ctrl-C
 * @: the signal number
 * Return: void
 */
void sigintHandler(__attribute__((unused))int ch)
{
_puts("\n");
_puts("$ ");
_putchar(BUF_FLUSH);
}
