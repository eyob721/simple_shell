#include "../shell.h"

/**
 * main - program to display the arguments passed to it
 * @ac: argument count
 * @av: argumnet vector
 *
 * Return: 0 on success, or 1 on error
 */
int main(int ac, char **av)
{
	int i = 0;

	_printf("count = [%d]\n", ac);
	while (*av != NULL)
		_printf("arg[%d]: [%s]\n", i++, *(av++));

	return (0);
}
