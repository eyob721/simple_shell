#include "../shell.h"

/**
 * main - test program for stat function call
 *
 * Return: 0 on success, or 1 on Error
 */
int main(void)
{
	int i = 0, stat_result;
	struct stat stat_buff;
	char *paths[] = {
		"/bin/ls",
		"/usr/bin/ls",
			".",
		"/usr/holberton",
			NULL
	};

	while (paths[i] != NULL)
	{
		stat_result = stat(paths[i], &stat_buff);
		if (stat_result == 0) /* File is found */
			_printf("%s: FILE IS FOUND\n", paths[i]);
		else
			_printf("%s: FILE IS NOT FOUND\n", paths[i]);
		++i;
	}
	return (EXIT_SUCCESS);
}
