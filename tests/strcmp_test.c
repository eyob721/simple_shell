#include "../shell.h"
#include <string.h>

typedef struct str_sets
{
	char *one;
	char *two;
} str_t;

/**
 * main - test program for strcmp and strncmp function
 *
 * Return: 0 on success, or 1 on failure
 */
int main(void)
{
	str_t str[] = {
		{"Holberton", "Holbeerton"},
		{"Holberton", "Holberton"},
		{"", "Holberton"},
		{"", ""},
		{NULL, NULL}
	};
	int i = 0;

	_printf("------------------------------------------------------------\n");
	_printf("                       STRCMP\n");
	_printf("------------------------------------------------------------\n");
	i = 0;

	while (str[i].one != NULL)
	{
		_printf("str1:[%s], str2:[%s]\n", str[i].one, str[i].two);
		_printf("[GOT]: [%d]\n", _strcmp(str[i].one, str[i].two));
		_printf("[EXP]: [%d]\n", strcmp(str[i].one, str[i].two));
		++i;
	}

	_printf("------------------------------------------------------------\n");
	_printf("                       STRNCMP\n");
	_printf("------------------------------------------------------------\n");
	i = 0;

	while (str[i].one != NULL)
	{
		_printf("str1:[%s], str2:[%s]\n", str[i].one, str[i].two);
		_printf("[GOT]: [%d]\n", _strncmp(str[i].one, str[i].two, 20));
		_printf("[EXP]: [%d]\n", strncmp(str[i].one, str[i].two, 20));
		++i;
	}
	return (1);
}
