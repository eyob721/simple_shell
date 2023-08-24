#include "shell.h"

/**
 * free_string_array - frees an allocated array of strings
 * @str_arr: allocated string array
 * @height: height of the allocated array
 *
 * Return: void
 */
void free_string_array(char **str_arr, int height)
{
	int i;

	if (str_arr == NULL || height < 0)
		return;
	for (i = 0; i < height; i++)
		free(str_arr[i]);
	free(str_arr);
}

/**
 * free_environ - frees the allocated environ
 *
 * Return: void
 */
void free_environ(void)
{
	int i = 0;

	if (environ == NULL)
		return;
	while (environ[i] != NULL)
		free(environ[i++]);
	free(environ);
}

/**
 * free_alias_list - a function that frees the alias list
 * @head: head of the alias list
 *
 * Return: void
 */
void free_alias_list(alias_t *head)
{
	alias_t *tmp;

	while (head != NULL)
	{
		tmp = head;
		head = head->next;
		free(tmp->alias_name);
		free(tmp->real_name);
		free(tmp);
	}
}
