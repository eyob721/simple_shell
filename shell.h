#ifndef SHELL_H
#define SHELL_H

/* -------------------------------------------------------------------------- */
/*                       HEADERS AND GLOBAL CONSTANTS                         */
/* -------------------------------------------------------------------------- */
/* STANDARD HEADERS */
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdarg.h>
#include <wait.h>
#include <sys/stat.h>

/* CUSTOM HEADERS */
#include "lib.h"

/* GLOBAL CONSTANTS  */
#define OPEN_ERR -1 /* Error code in opening a file descriptor */
#define READ_ERR -1 /* Error code of the read system call */
#define READ_EOF 0 /* End of File code of the read system call */
#define INTERACTIVE_MODE 1 /* Constant used to indicate interactive mode */

extern char **environ;

/* -------------------------------------------------------------------------- */
/*                               UTILITIES                                    */
/* -------------------------------------------------------------------------- */

/* INPUT UTILS */
#define LINE_BUFF_SIZE 128 /* Buffer size for taking line input */
#define STDIN_INPUT 0 /* Constant used to indicate an input is from stdin */
#define FILE_INPUT 1 /* Constant used to indicate an input is from a file */
int read_line(int fd, char **line_buff, int *line_size);
int read_from_stdin(char **line_buff, int *line_size);
int read_from_file(int fd, char **line_buff, int *line_size);

/* ARGUMENT UTILS */
#define SPACE 0 /* Constant used in a state machine */
#define ARGUMENT  1 /* Constant used in a state machine */
int get_argument_count(char *str);
char **get_argument_vector(char *str, int argc);
char *get_argument_end(char *arg_start);
void remove_quotations(char *arg_start, char **arg_end);

/* GENERAL UTILS */
#define FILE_FOUND 0
#define CHDIR_ERR -1
#define STAT_ERR -1
char *concat_strings(unsigned int n, ...);
char *_which(char *file, char *path);

/* CLEANUP UTILS */
void free_string_array(char **str_arr, int height);


/* -------------------------------------------------------------------------- */
/*                          SUPER SIMPLE SHELL                                */
/* -------------------------------------------------------------------------- */

/**
 * struct command_data: data structure to hold information of the a command
 * @cmd_argc: the argument count of a command
 * @cmd_argv: the argument vector of a command
 * @cmd_line_no: the current line number of a command
 */
typedef struct command_data {
	int cmd_argc;
	char **cmd_argv;
	int cmd_line_no;
} cmd_data_t;

/* Executor for binary commands */
int execute_binary(cmd_data_t *cmd);

#endif
