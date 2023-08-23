#include "../shell.h"

/**
 * main - program to test concat_string function
 *
 * Return: 0 on success, or 1 on error
 */
int main(void)
{
	char *cat_str = NULL;
	int i = 0;

	_printf("Test %d: -----------------------------------------\n", i++);
	cat_str = concat_strings(3, "Hello", " ", "World");
	if (cat_str != NULL)
		_printf("GOT: [%s]\n", cat_str);
	free(cat_str);

	_printf("Test %d: -----------------------------------------\n", i++);
	cat_str = concat_strings(3, "", "", "");
	if (cat_str != NULL)
		_printf("GOT: [%s]\n", cat_str);
	free(cat_str);

	_printf("Test %d: -----------------------------------------\n", i++);
	cat_str = concat_strings(4, "Hello", " ", "World.", " Alx is awesome!");
	if (cat_str != NULL)
		_printf("GOT: [%s]\n", cat_str);
	free(cat_str);

	return (0);
}
