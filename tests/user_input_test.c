#include "../shell.h"

/**
 * main - test program for read_line function
 * @ac: argument count
 * @av: argument vector
 *
 * Return: 0 on success, or 1 on error
 */
int main(int ac, char **av)
{
	int fd, mode, bytes_read;
	int line_size = 0, line_pos = 0;
	char *line_buff = NULL, *line_start = NULL;

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			_dprintf(STDERR_FILENO, "File not found\n");
			return (1);
		}
	}
	else
		fd = STDIN_FILENO;
	mode = isatty(fd);
	do {
		if (mode == INTERACTIVE_MODE)
		{
			_printf("(prompt): ");
			fflush(stdout);
		}
		bytes_read = read_line(fd, &line_buff, &line_size, &line_start, &line_pos);
		if (_strcmp(line_buff, "exit") == 0)
			break;
		if (bytes_read != READ_EOF && bytes_read != READ_ERR)
		{
			_printf("line -> [%s]\n", line_buff);
			_printf("read -> [%d]\n", bytes_read);
		}
	} while (bytes_read != READ_EOF && bytes_read != READ_ERR);
	free(line_buff);
	return (0);
}
