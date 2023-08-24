#include "shell.h"

/**
 * cmd_tok - a function used to tokenize the command line to get commands.
 * @cmd_line: pointer to the command line
 * @next_cmd: double pointer used to save the next command starting point
 * @next_opr: pointer used to save the next operator character
 *
 * Return: a command in the command line
 */
char *cmd_tok(char *cmd_line, char **next_cmd, char *next_opr)
{
	char *cmd_start = NULL, *skip_chars = " ;&|", *opr_chars = ";&|";

	if (cmd_line == NULL && *next_cmd == NULL)
		return (NULL);
	/* Determine starting point */
	cmd_start = cmd_line != NULL ? cmd_line : *next_cmd;
	/* Skip all skippable charaters, at the start of the command */
	while (*cmd_start != '\0' && _strchr(skip_chars, *cmd_start) != NULL)
		++cmd_start;
	/* If there are no more commands, return NULL */
	if (*cmd_start == '\0')
		return (NULL);
	/* Find the next command and operator */
	*next_cmd = _strpbrk(cmd_start, opr_chars);
	if (*next_cmd != NULL)
	{
		*next_opr = **next_cmd; /* Save the next operator character */
		**next_cmd = '\0';		/* Terminate current command */
		++(*next_cmd);			/* Go to the next starting point */
	}
	return (cmd_start);
}

/**
 * remove_comments - removes comments from a command line
 * @cmd_line: the command line
 *
 * Return: pointer to the edited command line
 */
char *remove_comments(char *cmd_line)
{
	return (cmd_line);
}
