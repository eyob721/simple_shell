#include "../shell.h"
#define TEST_SIZE 2

/**
 * main - test for shell argument utilities
 *
 * Return: 0 on success, or 1 on error
 */
int main(void)
{
	char tests[][40] = {
		"echo \"",
		"echo \"Hello World",
		"echo \"Hello World\"",
		"hello\"inside quotes\"World",
		"hello\"inside \'single\' quotes\"World",
		"one\"two\"three\'four\'",
		"one\"two\"three\'four\'five",
		"one\"two\"three\'four\'five another\'single\'",
		" ",
			""
	};
	int i = 0, j = 0, argc;
	char **argv;

	for (i = 0; tests[i][0] != '\0'; ++i)
	{
		_printf("Test [%d]: ----------------------------------------\n", i);
		argc = get_argument_count(tests[i]);
		_printf("argc = [%d]\n", argc);

		argv = get_argument_vector(tests[i], argc);
		if (argv == NULL)
			_dprintf(STDERR_FILENO, "[Test %d]: argv is NULL\n", i);
		else
		{
			for (j = 0; j < argc; ++j)
				_printf("argv[%d]: [%s]\n", j, argv[j]);
			free_string_array(argv, argc);
		}
		_printf("\n");
	}
	return (0);
}
