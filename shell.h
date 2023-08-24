#ifndef SHELL_H
#define SHELL_H

/* ------------------------------------------------------------------------- */
/*                 SHELL - HEADERS, GLOBALS, AND CONSTANTS                   */
/* ------------------------------------------------------------------------- */
/* LIBRARY HEADER */
#include "lib.h"

/* CONSTANTS  */
#define OPEN_ERR -1
#define READ_EOF 0
#define READ_ERR -1
#define INTERACTIVE_MODE 1

#define LINE_BUFF_SIZE 128
#define STDIN_INPUT 0
#define FILE_INPUT 1

#define SPACE 0
#define ARGUMENT  1

/* EXIT CODES */
#define CMD_EXIT_FAILURE 2
#define CMD_NOT_FOUND 127

extern char **environ;

/* ------------------------------------------------------------------------- */
/*                       SHELL - DATA STRUCTURES                             */
/* ------------------------------------------------------------------------- */

/**
 * struct shell_alias - a data structure used for alias list
 * @alias_name: the alias name
 * @real_name: the real name
 * @next: pointer to the next alias node
 */
typedef struct shell_alias
{
	char *alias_name;
	char *real_name;
	struct shell_alias *next;
} alias_t;

/**
 * struct shell_data - data structure used to pass informations needed to
 *                     executor functions.
 * @prg_name: the shell program name (av[0] of the shell program)
 * @line_buff: line buffer
 * @line_size: line buffer size
 * @cmd_ac: the argument count of a command
 * @cmd_av: the argument vector of a command
 * @line_no: the current line number of a command
 * @exit_code: the exit code of an executed command
 * @env_count: the number of variables in the environ
 * @env_cur_start: pointer to the start of newly added variables in the
 *                 environ copy
 * @env_cur_end: pointer to the end of the environ copy
 * @alias_head: head of the alias list
 * @alias_tail: tail of the alias list
 *
 * Description:
 *     - The `env_cur_start` is used for tracking newly allocated variables. It
 *       will point to the start of newly allocated variables in the environ.
 *       This is useful to keep track freeable memories.
 *     - The `env_cur_end` is used for adding ne variables to the environ.
 *       Instead of searching for the end of the environ array, we use the
 *       `env_cur_end` to add a variable. Just like you will use a tail in
 *       linked list.
 */
typedef struct shell_data
{
	char *prg_name;
	char *line_buff;
	int line_size;
	int cmd_ac;
	char **cmd_av; /* FREE this */
	int line_no;
	int exit_code;
	int env_count;
	char **env_cur_start;
	char **env_cur_end;
	alias_t *alias_head;
	alias_t *alias_tail;
} shell_t;

/**
 * struct executor - data structure used for fetching command executors
 * @cmd: command that the executor function handles
 * @executor: function pointer to the executor function
 */
typedef struct executor
{
	char *cmd;
	void (*executor)(shell_t *sh);
} executor_t;

/* ------------------------------------------------------------------------- */
/*                               SHELL - MAIN                                */
/* ------------------------------------------------------------------------- */

void initialize_shell_data(shell_t *sh, char **av);
void execute_commands(shell_t *sh);
void (*get_executor(char *given_cmd))(shell_t *cmd);

/* ------------------------------------------------------------------------- */
/*                            SHELL - UTILITIES                              */
/* ------------------------------------------------------------------------- */

/* GENERAL UTILS */
char *concat_strings(unsigned int n, ...);
char *_which(char *file);
int is_integer(char *str);

/* INPUT UTILS */
int read_line(int fd, char **line_buff, int *line_size);
int read_line_char(int fd, char **line_buff, int *line_size);

/* ARGUMENT UTILS */
int get_argument_count(char *str);
char **get_argument_vector(char *str, int argc);
char *get_argument_end(char *arg_start);
void remove_quotations(char *arg_start, char **arg_end);

/* CLEANUP UTILS */
void free_string_array(char **str_arr, int height);
void free_environ(char **env_cur_start);
void free_alias_list(alias_t *head);

/* ENVIRONMENT UTILS */
void _printenv(char *var);
char *_getenv(const char *var);
int get_environ_count(void);
char **get_environ_copy(int count);
char **get_env_ptr(char *var);

/* COMMAND UTILS */
char *cmd_tok(char *cmd_line, char **next_cmd, char *next_opr);

/* ALIAS UTILS */
void print_alias_list(alias_t *head);
int print_alias_node(alias_t *head, char *given_name);
int add_alias_node(alias_t **head, alias_t **tail, char *node);
alias_t *search_alias_list(alias_t *head, char *given_name);
char *substitute_alias_cmd(alias_t *head, char *cmd);

/* TEST UTILS */
void _printenv_test(int env_count, char **env_cur_start, char **env_cur_end);

/* ------------------------------------------------------------------------- */
/*                            SHELL - EXECUTORS                              */
/* ------------------------------------------------------------------------- */

void execute_builtin_exit(shell_t *cmd);
void execute_builtin_env(shell_t *sh);
void execute_builtin_unsetenv(shell_t *sh);
void execute_builtin_setenv(shell_t *sh);
void execute_builtin_cd(shell_t *sh);
void execute_builtin_alias(shell_t *sh);
void execute_system(shell_t *cmd);

/* EXECUTOR FUNCTIONS */
int _unsetenv(char *var, shell_t *sh);
int _setenv(char *var, char *value, shell_t *sh);
char **build_new_environ(shell_t *sh, char **vp, char *nv, int ne_sz);

void handle_cd_error(shell_t *sh);
int cd_home(char *path);
int cd_previous(void);
int cd_path(char *given_path);

/* ------------------------------------------------------------------------- */
#endif
