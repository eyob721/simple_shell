#include "shell.h"

/**
 * _printenv_test - prints the environment with test data
 * @env_count: the number of variables in the environ
 *
 * Return: void
 */
void _printenv_test(int env_count)
{
	int i = 0;
	char **env_ptr = environ;

	if (environ == NULL)
		return;
	_printf("count = [%d]\n", env_count);
	_printf("  [environ][%p] -> [%d][%s]\n", env_ptr, i, *(env_ptr));
	while (environ[i] != NULL) /* <= for printing the NULL */
	{
		++i, ++env_ptr;
		_printf("           [%p] -> [%d][%s]\n", env_ptr, i, *env_ptr);
	}
}

