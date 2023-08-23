#include "lib.h"
#include "shell.h"

/**
 * concat_strings - a function that concatenates any number of strings
 * @n: number of strings to concatenate
 *
 * Return: a newly allocated concatenated string, or NULL if error occurs
 */
char *concat_strings(unsigned int n, ...)
{
	unsigned int i = 0, cat_str_size = 0, arg_str_len = 0;
	char *cat_str = NULL, *arg_str;
	va_list args;

	if (n == 0)
		return (NULL);
	cat_str = _strdup("");
	if (cat_str == NULL)
		return (NULL);
	cat_str_size = 1;
	va_start(args, n);
	while (i < n)
	{
		arg_str = va_arg(args, char *);
		if (arg_str == NULL)
		{
			free(cat_str);
			return (NULL);
		}
		arg_str_len = _strlen(arg_str);
		cat_str = _realloc(cat_str, cat_str_size, cat_str_size + arg_str_len);
		if (cat_str == NULL)
			break;
		cat_str_size += arg_str_len;
		_strcat(cat_str, arg_str);
		++i;
	}
	va_end(args);
	return (cat_str);
}

/**
 * _which - a function that searches for a binary file (i.e. executable file)
 * @file: name of the file
 *
 * Return: Absolute path of to the file, if the file is found.
 *         NULL is returned if there is an error, or if the file is not found
 * Description: There are two cases here,
 *     - CASE 1 = 'file' string is a path to the file it self, that means it
 *       either starts with the  '/' character (absolute file path) or it
 *       starts with a '.' character (relative file path)
 *            - Here the file path is first checked if it exists and that the
 *              file is a binary file, not a directory or anything.
 *            - If the file is a binary file, then the file path is duplicated
 *              and returned. Otherwise NULL is returned
 *     - CASE 2 = 'file' string is a file name, in which case the function will
 *       look for the file in the PATH directories
 *            - Here the function checks if a binary file with the given file
 *              name exists in the PATH directories.
 *            - The function does that by first constructing an absolute path
 *              of a path in the PATH variable and the file name.
 *            - It uses a local buffer to do this. (i.e. path + "/" + file)
 *            - Then after constructing the absolute path it checks if the file
 *              exists using the constructed absolute path and that is is a
 *              binary file.
 *            - It does this for every path in the PATH variable until the file
 *              is found, in which case it will send a duplicate of the
 *              absolute file path.
 *            - Otherwise if the file is not found NULL will be returned.
 */
char *_which(char *file)
{
	int path_len, file_found = 0, file_is_binary = 0;
	char path_buf[PATH_MAX] = {0}, *env_path, *path_ptr, *colon_ptr;
	struct stat sb;

	if (file == NULL || *file == '\0')
		return (NULL);

	/* CASE 1: 'file' is a file path, so check if it is a binary file */
	if (*file == '/' || *file == '.')
	{
		file_found = stat(file, &sb) == 0;
		file_is_binary = file_found ? (sb.st_mode & S_IFMT) == S_IFREG : 0;
		if (file_is_binary)
			return (_strdup(file));
		return (NULL);
	}
	/* CASE 2: 'file' is a file name, so check the PATH directories */
	env_path = _getenv("PATH");
	if (env_path == NULL)
		return (NULL);
	path_ptr = env_path;
	colon_ptr = _strchr(path_ptr, ':');
	while (colon_ptr != NULL)
	{
		/* Construct an absolute file path */
		path_len = colon_ptr - path_ptr;
		_memcpy(path_buf, path_ptr, path_len);
		path_buf[path_len] = '\0';
		_strcat(path_buf, "/");
		_strcat(path_buf, file);
		/* Check if the file exists, and that it is a binary file */
		file_found = stat(path_buf, &sb) == 0;
		file_is_binary = file_found ? (sb.st_mode & S_IFMT) == S_IFREG : 0;
		if (file_is_binary)
			return (_strdup(path_buf));
		/* Move to the next path in the PATH variable */
		path_ptr = colon_ptr + 1;
		colon_ptr = _strchr(path_ptr, ':');
	}
	return (NULL);
}

/**
 * is_integer - a function that check if a given string is an integer string
 * @str: a string
 *
 * Return: 1 if the string is an integer, 0 otherwise
 */
int is_integer(char *str)
{
	int i = 0;

	if (str == NULL)
		return (0);
	while (str[i] != '\0')
	{
		if (!_isdigit(str[i]))
			return (0);
		++i;
	}
	return (1);
}
