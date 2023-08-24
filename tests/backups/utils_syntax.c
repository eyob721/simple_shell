#include "../shell.h"

/**
 * validabe_syntax - a function that validates the syntax of a command
 * @cmd: command
 *
 * Return: 1 if the syntax is valid
 *         0 if it is not valid, or
 *         -1 if there is an error
 * Description: This functions checks for known syntax errors, in this project
 *              only cases of unterminated quoted strings are handled.
 */
int validate_syntax(char *cmd)
{
	char qt_char = 0, *quotes = "\'\"`", *qt_start = NULL, *qt_end = NULL;
	int cmd_has_quotes = 0;

	if (cmd == NULL)
		return (-1);
	do {
		/* Find the start quote */
		qt_start = _strpbrk(cmd, quotes);
		if (qt_start == NULL)
			break;
		/* Save the quote character */
		qt_char = *qt_start;
		/* Find the end quote */
		qt_end = _strchr(++qt_start, qt_char);
		if (qt_end == NULL)
			return (0);
		qt_start = qt_end + 1;
	} while (cmd_has_quotes);
	return (1);
}

