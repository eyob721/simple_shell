#include "shell.h"
#include <stdlib.h>

/**
 * execute_builtin_exit - executes the builtin command 'exit'
 * @sh: pointer to the shell data
 *
 * Return: void
 */
void execute_builtin_exit(shell_t *sh)
{
	if (sh->cmd_av[1] == NULL)
		return;
	if (is_integer(sh->cmd_av[1]) == 0)
	{
		_dprintf(STDERR_FILENO, "%s: %d: exit: Illegal number: %s\n",
				sh->prg_name, sh->line_no, sh->cmd_av[1]);
		sh->exit_code = EXIT_FAILURE;
		return;
	}
	sh->exit_code = _atoi(sh->cmd_av[1]);
}
