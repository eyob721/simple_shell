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
		**next_cmd = '\0'; /* Terminate current command */
		++(*next_cmd); /* Go to the next starting point */
	}
	return (cmd_start);
}

/**
 * expand_variables - expandes variables in the cmd
 * @exit_code: exit code of the last command run
 * @cmd: command
 *
 * Return: command with the variables expanded, NULL otherwise.
 * Description:
 *     - A buffer is used to write the new command with the variables expanded
 *       to their corresponding value.
 */
char *expand_variables(int exit_code, char *cmd)
{
	int pos = 0, s = CMD_BUF_SIZE, state = WORD;
	char *cmd_buf = NULL, *c = NULL;
	char *var = NULL, *value = NULL, *v = NULL;

	cmd_buf = _realloc(cmd_buf, 0, s);
	if (cmd_buf == NULL)
		return (NULL);
	c = cmd;
	while (c && *c != '\0')
		switch (state)
		{
			case WORD:
				while (*c != '$' && *c != '\0')
					write_cmd_buf(*(c++), &cmd_buf, &pos, &s);
				state = VARIABLE;
				break;
			case VARIABLE:
				value = get_value(exit_code, &var, ++c);
				for (v = value; v != NULL && *v != '\0'; v++)
					write_cmd_buf(*v, &cmd_buf, &pos, &s);
				c = c + _strlen(var);
				free(var);
				free(value);
				var = NULL;
				value = NULL;
				state = WORD;
				break;
		}
	free(cmd);
	return (cmd_buf);
}

/**
 * write_cmd_buf - writes a character to the command buffer
 * @ch: character to be written on the command buffer
 * @cmd_buf: pointer to the command buffer
 * @pos: pointer to the next position to write in the command buffer
 * @sz: pointer to the size of the of the command buffer
 *
 * Return: void
 */
void write_cmd_buf(char ch, char **cmd_buf, int *pos, int *sz)
{
	if (*pos == *sz - 1)
	{
		*cmd_buf = _realloc(*cmd_buf, *sz, *sz + CMD_BUF_SIZE);
		*sz += CMD_BUF_SIZE;
	}
	(*cmd_buf)[(*pos)++] = ch;
}

/**
 * get_value - determines the value of a variable in the command
 * @exit_status: exit status of the shell, needed for $? variable
 * @var_ptr: double pointer to store the variable being expanded
 * @c: pointer to the current position in the command
 *
 * Description: the function while determining the value, stores the variable
 *				on the memory pointed by var_ptr in order to advance the
 *				position of c in the cmd string
 * Return: value of the variable if it exists, NULL otherwise
 */
char *get_value(int exit_status, char **var_ptr, char *c)
{
	char *str, *var_tmp, *value, *save_ptr = NULL;
	int pid = 0;

	if (c == NULL)
		return (NULL);
	str = _strdup(c);
	switch (*str)
	{
	case '$':
		var_tmp = "$";
		pid = getpid();
		value = _itoa(pid);
		break;
	case '?':
		var_tmp = "?";
		value = _itoa(exit_status);
		break;
	case ' ':
		var_tmp = " ";
		value = _strdup("$ ");
		break;
	case '\0':
		var_tmp = "";
		value = _strdup("$");
		break;
	default:
		var_tmp = _strtok_r(str, " $", &save_ptr);
		value = _strdup(_getenv(var_tmp));
		break;
	}
	*var_ptr = _strdup(var_tmp);
	free(str);
	return (value);
}

/**
 * remove_comments - removes comments from a command line
 * @cmd_line: the command line
 *
 * Return: pointer to the edited command line
 */
char *remove_comments(char *cmd_line)
{
	char *cmnt = NULL;
	int valid_comment = 0;

	if (cmd_line == NULL)
		return (NULL);

	cmnt = _strchr(cmd_line, '#');

	valid_comment = cmnt != NULL && (cmnt == cmd_line || *(cmnt - 1) == ' ');

	if (valid_comment)
		*cmnt = '\0';
	return (cmd_line);
}
