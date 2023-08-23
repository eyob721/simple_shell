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
 * @env_cur_start: pointer to the start of newly added variables in the
 *                 environ copy
 *
 * Return: void
 */
void free_environ(char **env_cur_start)
{
	if (environ == NULL)
		return;
	while (env_cur_start != NULL && *env_cur_start != NULL)
		free(*(env_cur_start++));
	free(environ);
}
