#include "shell.h"

/**
 * execute_builtin_unsetenv - executes the builtin command 'unsetenv'
 * @sh: pointer to the shell data
 *
 * Return: void
 */
void execute_builtin_unsetenv(shell_t *sh)
{
	int unset_success = 0;

	if (sh->cmd_ac != 2)
	{
		_dprintf(STDERR_FILENO, "%s: Usage: unsetenv VARIABLE\n", sh->cmd_av[0]);
		sh->exit_code = EC_CMD_EXIT_FAILURE;
		return;
	}
	unset_success = _unsetenv(sh->cmd_av[1], sh);
	if (!unset_success)
	{
		_dprintf(STDERR_FILENO, "%s: unsetenv failed\n", sh->cmd_av[0]);
		sh->exit_code = EXIT_FAILURE;
		return;
	}
	sh->exit_code = EXIT_SUCCESS;
}

/**
 * _unsetenv - a function that removes an environment variable
 * @var: a given variable
 * @sh: pointer to the shell data
 *
 * Return: 1 on success, or 0 on failure
 * Description:
 *     - The function uses the env_cur_start in the shell data to track of
 *       freeable memories.
 *     - Here are the steps taken
 *         - STEP 1: Handle edge cases
 *         - STEP 2: Determine if the variable exists
 *         - STEP 3: Build the new environ
 *         - STEP 4: Update environ
 */
int _unsetenv(char *var, shell_t *sh)
{
	int var_exists, var_has_equal_sign = 0;
	char **cur_env = environ, **new_env, **var_ptr;

	/* STEP 1: Handle edge cases, variable must not have an equal sign */
	var_has_equal_sign = _strchr(var, '=') != NULL;
	if (var_has_equal_sign)
		return (0);

	/* STEP 2: Determine if the variable exists */
	/* If the variable doesn't exist, there is nothing to remove */
	var_ptr = get_env_ptr(var);
	var_exists = var_ptr != NULL;
	if (!var_exists)
		return (1);

	/* At this point the variable exists and have to be removed */

	/* STEP 3: Build the new environ */
	new_env = build_new_environ(sh, var_ptr, NULL, sh->env_count);
	if (new_env == NULL)
		return (0);

	/* STEP 4: Update environ */
	environ = new_env;
	free(cur_env);
	return (1);
}
