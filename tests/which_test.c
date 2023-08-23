#include "../shell.h"

/**
 * main - test program for the _which function
 * @ac: argument count
 * @av: argument vector
 *
 * Return: 0 on success, or 1 on error
 */
int main(int ac, char **av)
{
	int i = 1;
	char *abs_file_path;

	if (ac < 2)
	{
		_dprintf(STDERR_FILENO, "Usage: _which filename ...\n");
		return (1);
	}

	while (av[i] != NULL)
	{
		abs_file_path = _which(av[i]);
		if (abs_file_path != NULL)
			_printf("%s\n", abs_file_path);
		free(abs_file_path);
		++i;
	}
	return (0);
}
