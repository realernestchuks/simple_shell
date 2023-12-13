#include "shell.h"

/**
 * _mycmd - determines if a file is an executable command
 * @shell: the shell struct
 * @path: path to the file
 * Return: 1 if true, 0 otherwise
 */
int _mycmd(shell_t *shell, char *path)
{
struct stat st;

(void)shell;
if (!path || stat(path, &st))
return (0);

if (st.st_mode & S_IFREG)
{
return (1);
}
return (0);
}

/**
 * dup_charset - duplicates characters
 * @pathstr: the PATH string
 * @begin: starting idx
 * @end: stopping idx
 * Return: pointer to new buffer
 */
char *dup_charset(char *pathstr, int begin, int end)
{
static char buf[1024];
int a = 0, k = 0;

for (k = 0, a = begin; a < end; a++)
if (pathstr[a] != ':')
buf[k++] = pathstr[a];
buf[k] = 0;
return (buf);
}

/**
* search_path - finds this cmd in the PATH string
* @shell: the shell struct
* @pathstr: the PATH string
* @cmd: the cmd to find
* Return: full path of cmd if found or NULL
*/
char *search_path(shell_t *shell, char *pathstr, char *cmd)
{
int a = 0, current_pos = 0;
char *path;

if (!pathstr)
return (NULL);
if ((_strlen(cmd) > 2) && begins_with(cmd, "./"))
{
if (_mycmd(shell, cmd))
return (cmd);
}
while (1)
{
if (!pathstr[a] || pathstr[a] == ':')
{
path = dup_charset(pathstr, current_pos, a);
if (!*path)
_strcat(path, cmd);
else
{
_strcat(path, "/");
_strcat(path, cmd);
}
if (_mycmd(shell, path))
return (path);
if (!pathstr[a])
break;
current_pos = a;
}
a++;
}
return (NULL);
}
