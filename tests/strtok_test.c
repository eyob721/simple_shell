#include "../shell.h"

/**
 * main - test program for strtok function
 *
 * Return: 0 on success, or 1 on error
 */
int main(void)
{
	char str1[] = "      FirstToken    &&&& SecondToken&&|||ThirdToken||||||||";
	char str2[] = "";
	char str3[] = "OnlyToken";
	char *save_ptr = NULL;
	char *tok = NULL;

	_printf("Test 1--------------------------------------------------------\n");
	tok = _strtok_r(str1, " &|", &save_ptr);
	while (tok != NULL)
	{
		_printf("[tok1]: [%s]\n", tok);
		tok = _strtok_r(NULL, " &|", &save_ptr);
	}
	_printf("Test 2--------------------------------------------------------\n");
	tok = _strtok_r(str2, " &|", &save_ptr);
	while (tok != NULL)
	{
		_printf("[tok1]: [%s]\n", tok);
		tok = _strtok_r(NULL, " &|", &save_ptr);
	}
	_printf("Test 3--------------------------------------------------------\n");
	tok = _strtok_r(str3, " &|", &save_ptr);
	while (tok != NULL)
	{
		_printf("[tok1]: [%s]\n", tok);
		tok = _strtok_r(NULL, " &|", &save_ptr);
	}
	return (0);
}
