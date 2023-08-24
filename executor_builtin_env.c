#include "shell.h"

/**
 * execute_builtin_env - executes the builtin command 'env'
 * @sh: pointer to the shell data
 *
 * Return: void
 */
void execute_builtin_env(shell_t *sh)
{
	if (sh->cmd_ac == 1)
	{
		_printenv("*");
		sh->exit_code = EXIT_SUCCESS;
		return;
	}
	if (_strcmp("test", sh->cmd_av[1]) == 0)
		_printenv_test(sh->env_count);
	sh->exit_code = EXIT_FAILURE;
}
