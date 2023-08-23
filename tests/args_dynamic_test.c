#include "../shell.h"

/**
 * main - test for shell argument utilities
 * @ac: argument count
 * @av: argumnet vector
 *
 * Return: 0 on success, or 1 on error
 */
int main(int __attribute__((unused)) ac, char __attribute__((unused)) **av)
{
	int bytes_read, line_size = LINE_BUFF_SIZE;
	int i = 0, line_argc = -1, mode = isatty(STDIN_FILENO);
	char *line_buff = NULL, **line_argv = NULL;

	do {
		if (mode == INTERACTIVE_MODE)
		{
			_printf("(prompt): ");
			fflush(stdout);
		}

		bytes_read = read_line(STDIN_FILENO, &line_buff, &line_size);

		if (_strcmp(line_buff, "exit") == 0 || bytes_read == READ_EOF)
			break;

		line_argc = get_argument_count(line_buff);
		_printf("line_argc = [%d]\n", line_argc);

		line_argv = get_argument_vector(line_buff, line_argc);
		if (line_argv == NULL)
			break;
		for (i = 0; i < line_argc; ++i)
			_printf("line_argv[%d]: [%s]\n", i, line_argv[i]);
		free_string_array(line_argv, line_argc);

	} while (bytes_read != READ_EOF && bytes_read != READ_ERR);
	free(line_buff);
	return (0);
}
