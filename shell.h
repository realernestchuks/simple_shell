#ifndef _SHELL_H
#define _SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* Constants for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* Constants for command chaining */
#define CMD_NORM 0
#define CMD_OR 1
#define CMD_AND 2
#define CMD_CHAIN 3

/* Constants for convert_num() */
#define CONVERT_LOWERCASE 1
#define CONVERT_UNSIGNED 2

/* Configuration: 1 if using system obtainline() */
#define USE_OBTAINLINE 0
#define USE_STRTOK 0

#define REC_FILE ".simple_shell_record"
#define REC_MAX 4096

/* External environment variable */
extern char **environ;

/**
* Linked list structure for strings
*/
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
*Structure containing pseudo-arguments for functions
*/
typedef struct passshell
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int totallines_label;
	char *ftitle;
	list_t *env;
	list_t *record;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* Pointer to cmd ; chain buffer, for memory management */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int reccount;
} shell_t;

#define shell_INIT \
	{ NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0 }

/**
* Structure for built-in commands
*/
typedef struct builtin
{
	char *type;
	int (*func)(shell_t *shell);
} builtin_table;

/* Function prototypes */

/**
*Implements shell loop functions for the main execution of a shell,
*searching for built-in commands, locating external commands,
*and forking and executing commands.
*/
int hsh(shell_t *shell, char **argvec);
int locate_builtin(shell_t *shell);
void locate_command(shell_t *shell);
void fork_command(shell_t *shell);
char *search_path(shell_t *shell, char *env_path, char *command);

/**
*Provides parser functions for executing commands with 
*specified file paths,copying characters from a string,
*and finding the full path of a command in the PATH string.
*/
int _mycmd(shell_t *shell, char *path);
char *dup_charset(char *pathstr, int begin, int stop);
char *find_path(shell_t *shell, char *pathstr, char *cmd);

/* Main shell loop */
int loophsh(char **);

/** 
*Provides error handling functions for printing strings
*and characters with buffering to standard output,
*error, and a specified file descriptor.
*/
void _myputs(char *str);
int _putchars(char ch);
int _myputfd(char ch, int fd);
int _myputsfd(char *str, int fd);

/**
*String manipulation functions: calculates the length of a string,
*compares two strings, checks if a string begins with
*a specified prefix, and concatenates two strings.
*/
int _strlen(char *str);
int _strcmp(char *str1, char *str2);
char *begins_with(const char *chr, const char *prefix);
char *_strcat(char *destination, char *source);

/**
*String manipulation functions continued:
*copies the string 'source' to 'destination',
*duplicates the string 'str', prints a string
*'str' to stdout, and writes a character 'ch' to stdout.
*/
char *_strcpy(char *destination, char *source);
char *_strdup(const char *str);
void _puts(char *str);
int _putchar(char ch);

/* Utility functions for exits */
char *_strncpy(char *destination, char *str, int n);
char *_strncat(char *destination, char *str, int n);
char *_strchr(char *str, char d);
char *strchr (const char *__s, int __ch);

/**
*Tokenization functions: splits the string 'str'
*into an array of strings using multiple delimiters
*specified in 'dstr', and splits the string 'str'
*into an array of strings using a single delimiter 'dstr'.
*/
char **strtow(char *str, char *deli);
char **strtow2(char *str, char deli);

/**
*Provides memory management functions for filling memory with a
*specified value, freeing an array of strings,
*and reallocating memory for a block.
*/
char *_memset(char *ptr, char j, unsigned int n);
void release_memory(char **pptr);
void *_realloc(void *ptr, unsigned int previous_size, unsigned int updated_size);

/**
*Provides a function for freeing memory
*associated with a pointer and setting it to NULL.
*/
int bfree(void **ptr);

/**
*Determines if the shell is in interactive mode,
*checks if a character is a delimiter, 
*checks for an alphabetic character, 
*and converts a string to an integer.
*/
int interactive(shell_t *shell);
int is_delimeter(char ch, char *delim);
int _isalpha(int ch);
int _atoi(char *s);
char *obtaincwd(char *buf, size_t size);

/* Error handling functions */
int _strtoi(char *s);
void log_error(shell_t *shell, char *errstring);
int print_number(int insert, int fd);
char *convert_num(long int num, int base, int labels);
void delete_comments(char *buf);

/**
*Exits the shell with a given exit status (0 if shell.argv[0] != "exit")
*changes the current directory of the process,
*and serves as a placeholder function for future implementation.
*/
int exit_shell(shell_t *shell);
int _cd(shell_t *shell);
int _process(shell_t *shell);

/**
*Displays the history list,
*manages aliases (add, remove),
*and mimics the alias built-in command.
*/
int record_list(shell_t *shell);
int handle_alias(shell_t *shell);
int remove_alias(shell_t *shell, char *str);
int put_alias(shell_t *shell, char *str);

/* Getline functions */
ssize_t obtain_input(shell_t *shell);
int _obtainline(shell_t *shell, char **ptr, size_t *length);
void sigintHandler(__attribute__((unused))int );
ssize_t read_buf(shell_t *shell, char *buf, size_t *a);
ssize_t insert_buf(shell_t *shell, char **buf, size_t *len);


/**
*Provides functions for removing, populating,
*and emptying information in shell-related data structures.
*/
void reset_shell(shell_t *shell);
void put_shell(shell_t *shell, char **argvec);
void free_shell(shell_t *shell, int all);

/**
*Retrieves, prints, sets, or removes environment variables,
*and populates the environment linked list.
*/
char *_obtainenv(shell_t *shell, const char *title);
int _myenviron(shell_t *shell);
int _myputenv(shell_t *shell);
int _myunputenv(shell_t *shell);
int occupy_env_list(shell_t *shell);

/**
*Provides functions for retrieving, unsetting,
*and setting environment variables in a shell environment.
*/
char **obtain_environ(shell_t *shell);
int _unputenv(shell_t *shell, char *var);
int _putenv(shell_t *shell, char *var, char *value);

/**
*Provides functions for managing command history records,
*including file I/O, list building, and renumbering.
*/
char *obtain_record_file(shell_t *shell);
int write_record(shell_t *shell);
int read_record(shell_t *shell);
int build_record_list(shell_t *shell, char *buf, int totallines);
int renumber_record(shell_t *shell);

/**
*Provides functions for manipulating linked lists,
*including node insertion, retrieval, removal, and list cleanup.
*/
list_t *add_node_alias(list_t **head, const char *str, int num);
list_t *add_node_alias_end(list_t **head, const char *str, int num);
size_t print_list_string(const list_t *g);
int remove_node_alias_at_idx(list_t **head, unsigned int idx);
void cleanup_list(list_t **head_ptr);

/**
*Provides additional functions for manipulating linked lists,
*including string length retrieval, list-to-string conversion,
*list length retrieval, finding nodes with specified prefixes,
*and getting the index of a node.
*/
size_t list_len(const list_t *h);
char **list_to_str(list_t *head);
size_t display_list(const list_t *h);
list_t *node_alias_begins_with(list_t *node_alias, char *prefixvalue, char ch);
ssize_t obtain_node_alias_idx(list_t *head, list_t *node_alias);

/**
*Variable handling functions: checks if 'buf' contains variable
*references in 'mychain', verifies and replaces variables in
*'buf' at specified addresses, changes aliases in the shell,
*changes variables in the shell, and replaces a string
*'old' with a new string 'new'.
*/
int validate_chain(shell_t *shell, char *buf, size_t * q);
void target_chain(shell_t *shell, char *buf, size_t *q, size_t a, size_t len);
int reinstate_alias(shell_t * shell);
int reinstate_vars(shell_t *shell);
int replace_string(char **previous, char *modified);

#endif
