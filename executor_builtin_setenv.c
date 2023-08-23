#include "lib.h"
#include "shell.h"

/**
 * execute_builtin_setenv - executes the builtin command 'setenv'
 * @sh: pointer to the shell data
 *
 * Return: void
 */
void execute_builtin_setenv(shell_t *sh)
{
	int set_success = 0;

	if (sh->cmd_ac != 3)
	{
		_dprintf(STDERR_FILENO, "%s: Usage: setenv VARIABLE VALUE\n",
				sh->cmd_av[0]);
		sh->exit_code = EC_CMD_EXIT_FAILURE;
		return;
	}
	set_success = _setenv(sh->cmd_av[1], sh->cmd_av[2], sh);
	if (!set_success)
	{
		_dprintf(STDERR_FILENO, "%s: setenv failed\n", sh->cmd_av[0]);
		sh->exit_code = EXIT_FAILURE;
		return;
	}
	sh->exit_code = EXIT_SUCCESS;
}

/**
 * _setenv - a function that add or overwrites an environment variable
 * @var: a given variable
 * @value: value of the variable
 * @sh: pointer to the shell data
 *
 * Return: 1 on success, or 0 on failure
 * Description:
 *     - The function uses the env_cur_start in the shell data to track of
 *       freeable memories.
 *     - Here are the steps taken
 *         - STEP 1: Handle edge cases
 *         - STEP 2: Determine if the variable exists
 *         - STEP 3: Allocate memory for the new variable and environ block
 *         - STEP 4: Build the new environ
 *         - STEP 5: Update environ
 */
int _setenv(char *var, char *value, shell_t *sh)
{
	int new_env_size, var_exists, var_has_equal_sign = 0;
	char **cur_env = environ, **new_env, **var_ptr, *new_var;

	/* STEP 1: Handle edge cases, variable must not have an equal sign */
	var_has_equal_sign = _strchr(var, '=') != NULL;
	if (var_has_equal_sign)
		return (0);

	/* STEP 2: Determine if the variable exists */
	var_ptr = get_env_ptr(var);
	var_exists = var_ptr != NULL;

	/* STEP 3: Allocate memory for the new variable and environ block */
	new_var = concat_strings(3, var, "=", value);
	if (new_var == NULL)
		return (0);
	new_env_size = var_exists ? sh->env_count + 1 : sh->env_count + 2;

	/* STEP 4: Build the new environ */
	new_env = build_new_environ(sh, var_ptr, new_var, new_env_size);
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
 * build_new_environ - a function that builds the new environ
 * @sh: pointer to the shell data
 * @vp: pointer to an existing variable
 * @nv: pointer to a new variable
 * @ne_sz: size of the new environ
 *
 * Return: void
 */
char **build_new_environ(shell_t *sh, char **vp, char *nv, int ne_sz)
{
	char **cur_env = environ, **new_env = NULL;
	int i_cur = 0, i_new = 0;
	int var_exists, var_is_freeable, adding_new_variable = nv != NULL;

	new_env = malloc(sizeof(char *) * ne_sz);
	if (new_env == NULL)
		return (NULL);

	/* If the variable exists, and is freeable, it must be removed */
	var_exists = vp != NULL;
	var_is_freeable = vp >= sh->env_cur_start;

	if (var_exists && var_is_freeable)
		free(*vp);

	/* Assign variables to the new environ */
	while (i_cur <= sh->env_count)
	{
		if (cur_env + i_cur == vp) /* Skip existing variable to remove it */
			++i_cur;
		new_env[i_new] = cur_env[i_cur];
		++i_cur, ++i_new;
	}
	if (adding_new_variable)
	{
		new_env[i_new - 1] = nv;
		new_env[i_new] = NULL;
	}

	/* Update the `env_cur_start`, `env_cur_end` and the `env_count` */
	sh->env_cur_start = new_env + (sh->env_cur_start - cur_env);
	sh->env_cur_end = new_env + i_new;
	if (var_exists && !var_is_freeable)
		--sh->env_cur_start;
	if (!adding_new_variable)
		--sh->env_cur_end;
	sh->env_count = ne_sz - 1;

	return (new_env);
}
