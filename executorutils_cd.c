#include "shell.h"

/**
 * handle_cd_error - handles error output and exit code for the cd command
 * @sh: pointer to the shell data
 *
 * Return: void
 */
void handle_cd_error(shell_t *sh)
{
	_dprintf(STDERR_FILENO, "%s: %d: %s: can't cd to %s\n", sh->prg_name,
			sh->line_no, sh->cmd_av[0], sh->cmd_av[1]);
	sh->exit_code = CMD_EXIT_FAILURE;
}

/**
 * cd_home - changes directory to HOME
 * @given_path: given path to cd
 *
 * Return: 0 on success, or -1 on error
 * Description:
 *     - In the case where the HOME doesn't exist, it is considered an error
 *       only if the argument is the tilde character (i.e. "~").
 *     - It will not be considered as an error, if there are no arguments
 *       passed (i.e. NULL).
 */
int cd_home(char *given_path)
{
	char *home_path = NULL;

	home_path = _getenv("HOME");
	if (given_path == NULL && home_path == NULL)
		return (0);
	else if (home_path == NULL)
		return (-1);
	return (chdir(home_path));
}

/**
 * cd_previous - changes directory back to OLDPWD
 *
 * Return: 0 on success, or -1 on error
 * Description: In the case where the OLDPWD doesn't exist, it will not be
 *              considered as an error, but rather he function will just
 *              simply not call chdir and return back.
 */
int cd_previous(void)
{
	char *prev_path = NULL;

	prev_path = _getenv("OLDPWD");
	if (prev_path == NULL)
		return (0);
	return (chdir(prev_path));
}

/**
 * cd_path - changes directory to the given path
 * @path: given path to cd
 *
 * Return: 0 on success, or -1 on error
 */
int cd_path(char *path)
{
	return (chdir(path));
}

