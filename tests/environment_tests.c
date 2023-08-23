#include "../shell.h"

/**
 * main - test program for environment functions
 * @ac: argument count
 * @av: argument vector
 *
 * Return: 0 on success, or 1 on error
 */
int main(void)
{
	int i = 0;
	char *value;
	char *var[] = {
		"PATH",
		"PWD",
		"",
		NULL
	};

	/* ----------------------------------------------------------------------*/
	/*                              PRINTENV                                 */
	/* ----------------------------------------------------------------------*/

	/* _printenv(NULL); */

	/* ----------------------------------------------------------------------*/
	/*                               GETENV                                  */
	/* ----------------------------------------------------------------------*/

	for (i = 0; var[i] != NULL; i++)
	{
		value = _getenv(var[i]);
		_printf("[%s]=[%s]\n", var[i], value);
	}

	return (0);
}
