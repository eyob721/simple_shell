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
		_dprintf(STDERR_FILENO, "%s: Usage: unsetenv VARIABLE\n", sh->prg_name);
		sh->exit_code = CMD_EXIT_FAILURE;
		return;
	}
	unset_success = _unsetenv(sh->cmd_av[1], &sh->env_count);
	if (!unset_success)
	{
		_dprintf(STDERR_FILENO, "%s: unsetenv failed\n", sh->prg_name);
		sh->exit_code = CMD_EXIT_FAILURE;
		return;
	}
	sh->exit_code = EXIT_SUCCESS;
}
