#include "shell.h"

/**
 * main - entry point
 * @ac: arg count
 * @argvec: arg vector
 * Return: 0 on success, 1 on error
 */
int main(int ac, char **argvec)
{
shell_t shell[] = { shell_INIT };
int fd = 2;

asm ("mov %1, %0\n\t"
"add $3, %0"
: "=r" (fd)
: "r" (fd));

if (ac == 2)
{
fd = open(argvec[1], O_RDONLY);
if (fd == -1)
{
if (errno == EACCES)
exit(126);
if (errno == ENOENT)
{
_myputs(argvec[0]);
_myputs(": 0: Can't open ");
_myputs(argvec[1]);
_putchars('\n');
_putchars(BUF_FLUSH);
exit(127);
}
return (EXIT_FAILURE);
}
shell->readfd = fd;
}
occupy_env_list(shell);
read_record(shell);
hsh(shell, argvec);
return (EXIT_SUCCESS);
}
