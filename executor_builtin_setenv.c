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
				sh->prg_name);
		sh->exit_code = CMD_EXIT_FAILURE;
		return;
	}
	set_success = _setenv(sh->cmd_av[1], sh->cmd_av[2], &sh->env_count);
	if (!set_success)
	{
		_dprintf(STDERR_FILENO, "%s: setenv failed\n", sh->prg_name);
		sh->exit_code = CMD_EXIT_FAILURE;
		return;
	}
	sh->exit_code = EXIT_SUCCESS;
}
