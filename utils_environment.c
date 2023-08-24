#include "shell.h"

/**
 * _printenv - prints part or all of the environment
 * @var: variable name
 *
 * Return: void
 */
void _printenv(char *var)
{
	int i = 0;
	char *value = NULL;

	if (environ == NULL || var == NULL)
		return;
	/* CASE 1: Print all the environment variables */
	if (_strcmp(var, "*") == 0)
	{
		for (i = 0; environ[i] != NULL; i++)
			_printf("%s\n", environ[i]);
		return;
	}
	/* CASE 2: Print a single variable, if it exists */
	value = _getenv(var);
	if (value != NULL)
		_printf("%s\n", value);
}

/**
 * _getenv - gets the value of a given variable in the environment
 * @var: variable name
 *
 * Return: value of the given variable in the environment, or NULL if the
 *         variable is not found.
 * Description: The variable `len` is used for the `strncmp` function to only
 *              compare the variable part of the environ element. It is the
 *              number of characters between the environ element starting point
 *              and the equal sign, i.e. the length of the variable part.
 */
char *_getenv(const char *var)
{
	int i = 0, len = 0, variable_is_found = 0;
	char *value = NULL, *eql_sign_ptr;

	if (environ == NULL || var == NULL)
		return (NULL);
	while (environ[i] != NULL)
	{
		/* Find the equal sign, in the environ element */
		eql_sign_ptr = _strchr(environ[i], '=');

		/* Find number of characters of the variable part */
		len = eql_sign_ptr - environ[i];

		/**
		 * Compare the variable part in the environ element,
		 * with the given variable string.
		 */
		if (_strncmp(environ[i], (char *)var, len) == 0)
		{
			variable_is_found = 1;
			break;
		}

		/* Go to the next environ element */
		++i;
	}
	if (variable_is_found)
		value = eql_sign_ptr + 1;
	return (value);
}

/**
 * get_environ_count - a function that counts the number of variables in the
 *                     environment variable environ
 *
 * Return: number of variables in the environ
 */
int get_environ_count(void)
{
	int i = 0;

	while (environ != NULL && environ[i] != NULL)
		++i;
	return (i);
}

/**
 * get_environ_copy - a function that copies the environ
 * @count: count of the environ variables
 *
 * Return: pointer to the copied environ array
 * Description:
 *     - The function does not duplicate the variables, but only the row
 *       of the environ variable.
 *     - Also if there are extra spaces in the new environ, they will be
 *       set to NULL.
 */
char **get_environ_copy(int count)
{
	int i = 0;
	char **env_copy = NULL;

	if (count == 0 || environ == NULL)
		return (NULL);

	/* Allocate memory for the environ copy */
	env_copy = malloc(sizeof(char *) * (count + 1)); /* +1 for NULL */
	if (env_copy == NULL)
		return (NULL);

	/* Copy environ variables */
	for (i = 0; environ[i] != NULL; ++i)
	{
		env_copy[i] = _strdup(environ[i]);
		if (env_copy[i] == NULL)
		{
			free_string_array(env_copy, i);
			return (NULL);
		}
	}
	env_copy[count] = NULL;

	return (env_copy);
}

/**
 * get_var_ptr - gets the address of a variable on the environ block (row)
 * @var: a variable
 *
 * Return: pointer to the row on the environ with the given variable, or
 *         NULL otherwise.
 */
char **get_var_ptr(char *var)
{
	int i = 0, len = 0, variable_is_found = 0;
	char **env_ptr = NULL, *eql_sign_ptr;

	if (environ == NULL || var == NULL)
		return (NULL);
	while (environ[i] != NULL)
	{
		/* Find the equal sign, in the environ element */
		eql_sign_ptr = _strchr(environ[i], '=');

		/* Find number of characters of the variable part */
		len = eql_sign_ptr - environ[i];

		/**
		 * Compare the variable part in the environ element,
		 * with the given variable string.
		 */
		if (_strncmp(environ[i], (char *)var, len) == 0)
		{
			variable_is_found = 1;
			break;
		}

		/* Go to the next environ element */
		++i;
	}
	if (variable_is_found)
		env_ptr = environ + i;
	return (env_ptr);
}
