#include "shell.h"

/**
 * obtain_record_file - obtains the record file
 * @shell: parameter struct
 * Return: allocated string containg record file
 */

char *obtain_record_file(shell_t *shell)
{
char *buf, *dir;

dir = _obtainenv(shell, "HOME=");
if (!dir)
return (NULL);
buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(REC_FILE) + 2));
if (!buf)
return (NULL);
buf[0] = 0;
_strcpy(buf, dir);
_strcat(buf, "/");
_strcat(buf, REC_FILE);
return (buf);
}

/**
 * write_record - creates a file, or appends to an existing file
 * @shell: the parameter struct
 * Return: 1 on success, else -1
 */
int write_record(shell_t *shell)
{
ssize_t fd;
char *filetitle = obtain_record_file(shell);
list_t *node_alias = NULL;

if (!filetitle)
return (-1);

fd = open(filetitle, O_CREAT | O_TRUNC | O_RDWR, 0644);
free(filetitle);
if (fd == -1)
return (-1);
for (node_alias = shell->record; node_alias; node_alias = node_alias->next)
{
_myputsfd(node_alias->str, fd);
_myputfd('\n', fd);
}
_myputfd(BUF_FLUSH, fd);
close(fd);
return (1);
}

/**
 * read_record - reads record from file
 * @shell: the parameter struct
 * Return: reccount on success, 0 otherwise
 */
int read_record(shell_t *shell)
{
int a, last = 0, totallines = 0;
ssize_t fd, rdlen, fsize = 0;
struct stat st;
char *buf = NULL, *filetitle = obtain_record_file(shell);

if (!filetitle)
return (0);

fd = open(filetitle, O_RDONLY);
free(filetitle);
if (fd == -1)
return (0);
if (!fstat(fd, &st))
fsize = st.st_size;
if (fsize < 2)
return (0);
buf = malloc(sizeof(char) * (fsize + 1));
if (!buf)
return (0);
rdlen = read(fd, buf, fsize);
buf[fsize] = 0;
if (rdlen <= 0)
return (free(buf), 0);
close(fd);
for (a = 0; a < fsize; a++)
if (buf[a] == '\n')
{
buf[a] = 0;
build_record_list(shell, buf + last, totallines++);
last = a + 1;
}
if (last != a)
build_record_list(shell, buf + last, totallines++);
free(buf);
shell->reccount = totallines;
while (shell->reccount-- >= REC_MAX)
remove_node_alias_at_idx(&(shell->record), 0);
renumber_record(shell);
return (shell->reccount);
}

/**
 * build_record_list - adds entry to a record linked list
 * @shell: Structure containing potential arguments. Used to maintain
 * @buf: buffer
 * @totallines: the record totallines, reccount
 * Return: Always 0
 */
int build_record_list(shell_t *shell, char *buf, int totallines)
{
list_t *node_alias = NULL;

if (shell->record)
node_alias = shell->record;
add_node_alias_end(&node_alias, buf, totallines);

if (!shell->record)
shell->record = node_alias;
return (0);
}

/**
 * renumber_record - renumbers the record linked list after changes
 * @shell: Structure containing potential arguments. Used to maintain
 * Return: the new reccount
 */
int renumber_record(shell_t *shell)
{
list_t *node_alias = shell->record;
int a = 0;

while (node_alias)
{
node_alias->num = a++;
node_alias = node_alias->next;
}
return (shell->reccount = a);
}
