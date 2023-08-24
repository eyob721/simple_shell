#include "shell.h"

/**
 * _setenv - a function that add or overwrites an environment variable
 * @var: a given variable
 * @value: value of the variable
 * @envc: pointer to the environ count
 *
 * Return: 1 on success, or 0 on failure
 * Description:
 *     - Here are the steps taken
 *         - STEP 1: Handle edge cases
 *         - STEP 2: Determine if the variable exists
 *         - STEP 3: Build the new environ variable
 *         - STEP 4: Build the new environ
 *         - STEP 5: Update environ
 */
int _setenv(char *var, char *value, int *envc)
{
	int new_env_size, var_exists, var_has_equal_sign = 0;
	char **cur_env = environ, **new_env, **var_ptr, *new_var;

	/* STEP 1: Handle edge cases, variable must not have an equal sign */
	var_has_equal_sign = _strchr(var, '=') != NULL;
	if (var_has_equal_sign)
		return (0);

	/* STEP 2: Determine if the variable exists */
	var_ptr = get_var_ptr(var);
	var_exists = var_ptr != NULL;

	/* STEP 3: Build the new environ variable */
	new_var = concat_strings(3, var, "=", value);
	if (new_var == NULL)
		return (0);

	/* STEP 4: Build the new environ */
	new_env_size = var_exists ? *envc + 1 : *envc + 2;
	new_env = build_new_environ(envc, var_ptr, new_var, new_env_size);
	if (new_env == NULL)
	{
		free(new_var);
		return (0);
	}

	/* STEP 5: Update environ */
	environ = new_env;
	free(cur_env);
	return (1);
}

/**
 * _unsetenv - a function that removes an environment variable
 * @var: a given variable
 * @envc: pointer to the environ count
 *
 * Return: 1 on success, or 0 on failure
 * Description:
 *     - Here are the steps taken
 *         - STEP 1: Handle edge cases
 *         - STEP 2: Determine if the variable exists
 *         - STEP 3: Build the new environ
 *         - STEP 4: Update environ
 */
int _unsetenv(char *var, int *envc)
{
	int var_exists, var_has_equal_sign = 0;
	char **cur_env = environ, **new_env, **var_ptr;

	/* STEP 1: Handle edge cases, variable must not have an equal sign */
	var_has_equal_sign = _strchr(var, '=') != NULL;
	if (var_has_equal_sign)
		return (0);

	/* STEP 2: Determine if the variable exists */
	/* If the variable doesn't exist, there is nothing to remove */
	var_ptr = get_var_ptr(var);
	var_exists = var_ptr != NULL;
	if (!var_exists)
		return (1);

	/* At this point the variable exists and has to be removed */

	/* STEP 3: Build the new environ */
	new_env = build_new_environ(envc, var_ptr, NULL, *envc);
	if (new_env == NULL)
		return (0);

	/* STEP 4: Update environ */
	environ = new_env;
	free(cur_env);
	return (1);
}

/**
 * build_new_environ - a function that builds the new environ
 * @envc: pointer to the environ count
 * @vp: pointer to an existing variable
 * @nv: pointer to a new variable
 * @ne_sz: size of the new environ
 *
 * Return: void
 * Description: There are 3 cases in building a new environ
 *     CASE 1:- Overwriting an existing variable
 *     CASE 2:- Removing an existing variable
 *     CASE 3:- Add a new variable
 */
char **build_new_environ(int *envc, char **vp, char *nv, int ne_sz)
{
	char **cur_env = environ, **new_env = NULL;
	int i_cur = 0, i_new = 0;
	int var_exists, adding_new_variable = nv != NULL;

	new_env = malloc(sizeof(char *) * ne_sz);
	if (new_env == NULL)
		return (NULL);

	/* Determine if the variable exists */
	var_exists = vp != NULL;

	/* Assign variables to the new environ */
	while (i_cur <= *envc)
	{
		if (cur_env + i_cur == vp) /* The existing variable is found */
		{
			free(cur_env[i_cur]);
			if (adding_new_variable && var_exists) /* Overwriting */
				cur_env[i_cur] = nv;
			else if (!adding_new_variable && var_exists) /* Removing */
				++i_cur;
		}
		new_env[i_new] = cur_env[i_cur];
		++i_cur, ++i_new;
	}
	if (adding_new_variable && !var_exists) /* Adding a new variable */
	{
		new_env[i_new - 1] = nv;
		new_env[i_new] = NULL;
	}

	/* Update the environ count */
	*envc = ne_sz - 1;

	return (new_env);
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
