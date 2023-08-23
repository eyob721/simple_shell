#include "../shell.h"

/**
 * main - a simple test program
 *
 * Return: 0 on sucess, or 1 on error
 */
int main(void)
{
	char *buffer = NULL;
	size_t size = 0;

	_printf("$ ");
	fflush(stdout);
	getline(&buffer, &size, stdin);
	_printf("input: [%s]\n", buffer);
	free(buffer);
	return (0);
}
