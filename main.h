#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>
#include <sys/stat.h>

#define BUFF_SIZE	1024
#define NO_VALID_CHAR	0
#define VALID_CHAR	1
#define NO		0
#define YES		1

/* echo */
#define PID		1
#define STAT		2
/***************************/


/**** for env ****/
typedef struct env
{
	char *name;
	char *equals;
	char *value;
	struct env *next;
} env_node;

env_node *env_list(char **env);
env_node *create_env_list(env_node **head, char *name, char *value);
env_node *create_env_node(char *name, char *value);
env_node *add_to_existing(env_node **head, char *name, char *value);
env_node *replace_env_node(env_node *node, char *name, char *value);
void delete_env_node(env_node *node, char *name);
void free_env_list(env_node *head);
/***************************/

/**
 * struct command - defines a command
 * @name: the name of the command
 * @op: the function pointer to the operation to be performed
*/

typedef struct command
{
	char *name;
	char *(*op)(char **arr_tokens, env_node *env_head, char *buffer);
} cmds;

extern char **environ;
static int status;

/* _getline */
ssize_t _getline(char **line_buff, size_t *capacity, FILE *stream);

/* _strtok */
char *_strtok(char *str, const char *delim);

/*prototypes for builtin functions*/
char *_exit_th(char **arr_tokens, env_node *env_head, char *buffer);
char *cd(char **arr_tokens, env_node *env_head, char *buffer);
char *_setenv(char **arr_tokens, env_node *env_head, char *buffer);
char *_putenv(char **arr_tokens, env_node *env_head, char *buffer);
char *builtins(char **arr_tokens, env_node *env_head, char *buffer);
char *_env(char **arr_tokens, env_node *env_head, char *buffer);

/* execve */
void exec_cmd(char *buffer, char **arr_tokens, char *cmd_full_path,
		env_node *env_head);

/* get */
char *get_tokens(char *buffer, char ***arr_tokens, env_node *head);
char *_getenv(char *var, env_node *env_head);
char *full_cmd(char *cmd, char *path);
char *_getcmd(char *cmd, char **arr_tokens, env_node *env_head);

/* echo */
char *sort_echo(char ***arr_tokens, env_node *env_head);
void handle_esc(char ***arr_tokens, char **string, size_t *str_len, size_t i,
		size_t *j);
char *mov_num_vals(char **string, size_t *str_len, size_t *str_size,
		size_t type, size_t *j, size_t *doll_flag);
char *mov_var_val(char ***arr_tokens, env_node *env_head, char **string,
		size_t *str_len, size_t *j, size_t i, size_t *doll_flag);
char *handle_exp(char ***arr_tokens, env_node *env_head, char **string,
		size_t *str_len, size_t *str_size, size_t *j, size_t i, size_t *doll_flag);

/* end */
void eof(char *buffer, env_node *env_head);
void error_exit(char *msg, env_node *env_head);
void exit_sh(char **arr_tokens, char *buffer, env_node *env_head);
void exit_fail(char *msg, char *buffer, char **arr_tokens, env_node *env_head);

/* utilities */
int write_to_stderr(char *format, char *arg_zero, size_t loop_count,
		char *tok_zero, char *tok_one);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
int _strcmp(char *s1, char *s2);
int _strncmp(char *, char *, size_t);
size_t _strlen(char *str);
char *_strchr(char *s, char c);
char *_strcat(char *dest, char *src);
char **_strtow(char *str);
char *_strcpy(char *, char *);
char *_strdup(char *);
char *str_concat(char *, char *);
char *_strstr(char *haystack, char *needle);
char *conv_to_char(size_t num);
int _atoi(char *s);

#endif /* for MAIN_H */
