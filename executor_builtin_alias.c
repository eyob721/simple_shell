#include "shell.h"

/**
 * execute_builtin_alias - executes the builtin command 'alias'
 * @sh: pointer to the shell data
 *
 * Return: void
 */
void execute_builtin_alias(shell_t *sh)
{
	int i, add_new_alias = 0, code_return = EXIT_SUCCESS;
	char *arg = NULL;

	if (sh->cmd_ac == 1)
	{
		print_alias_list(sh->alias_head);
		sh->exit_code = EXIT_SUCCESS;
		return;
	}
	for (i = 1; sh->cmd_av[i] != NULL; i++)
	{
		arg = sh->cmd_av[i];
		add_new_alias = *arg != '=' && _strchr(arg, '=') != NULL;
		if (add_new_alias)
		{
			code_return = add_alias_node(&sh->alias_head, &sh->alias_tail, arg);
			if (code_return == EXIT_FAILURE)
				perror(sh->prg_name);
		}
		else
		{
			code_return = print_alias_node(sh->alias_head, arg);
			if (code_return == EXIT_FAILURE)
				_dprintf(STDERR_FILENO, "alias: %s not found\n", arg);
		}
	}
	sh->exit_code = code_return;
}
