#include "shell.h"

/**
 * _printenv_test - prints the environment with test data
 * @env_count: the number of variables in the environ
 * @env_cur_start: pointer to the start of newly added variables in the
 *                 environ copy
 * @env_cur_end: pointer to the end of the environ copy
 *
 * Return: void
 */
void _printenv_test(int env_count, char **env_cur_start, char **env_cur_end)
{
	int i = 0;
	char **env_ptr = environ;

	if (environ == NULL)
		return;
	_printf("count = [%d]\n", env_count);
	while (environ[i] != NULL) /* <= for printing the NULL */
	{
		if (env_ptr == environ)
			_printf("  [environ][%p] -> [%d][%s]\n", env_ptr, i, *env_ptr);
		else if (env_ptr == env_cur_start)
			_printf("[cur_start][%p] -> [%d][%s]\n", env_ptr, i, *env_ptr);
		else
			_printf("           [%p] -> [%d][%s]\n", env_ptr, i, *env_ptr);
		++i, ++env_ptr;
	}
	if (env_ptr == env_cur_start)
		_printf("[cur_start][%p] -> [%d][%s]\n", env_ptr, i, *env_ptr);
	_printf("  [cur_end][%p] -> [%d][%s]\n", env_cur_end, i, *env_cur_end);
}

