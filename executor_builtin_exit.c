#include "shell.h"

/**
 * execute_builtin_exit - executes the builtin command 'exit'
 * @sh: pointer to the shell data
 *
 * Return: void
 */
void execute_builtin_exit(shell_t *sh)
{
	if (sh->cmd_ac >= 2)
	{
		if (is_integer(sh->cmd_av[1]) == 0)
		{
			_dprintf(STDERR_FILENO, "%s: %d: exit: Illegal number: %s\n",
					sh->prg_name, sh->line_no, sh->cmd_av[1]);
			sh->exit_code = CMD_EXIT_FAILURE;
			return;
		}
		sh->exit_code = _atoi(sh->cmd_av[1]);
	}

	free(sh->line_buff);
	free_environ();
	free_alias_list(sh->alias_head);
	free_string_array(sh->cmd_av, sh->cmd_ac);

	exit(sh->exit_code);
}
