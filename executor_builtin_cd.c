#include "lib.h"
#include "shell.h"

/**
 * execute_builtin_cd - executes the builtin command 'cd'
 * @sh: pointer to the shell data
 *
 * Return: void
 * Description: The function follows the following steps
 *     - STEP 1:- First get the OLDPWD path, which is the current directory
 *                path before changeing directory.
 *     - STPE 2:- Change to the given directory.
 *     - STEP 3:- Then get the PWD path, which is the current directory path
 *                after changeing directory.
 *              - Here the PWD must be printed, if the cd is given the argument
 *                "-", which cd to previous.
 *     - STEP 4:- Update PWD and OLDPWD in the environment.
 */
void execute_builtin_cd(shell_t *sh)
{
	char oldpwd[PATH_MAX] = {0}, pwd[PATH_MAX] = {0}, *path = sh->cmd_av[1];
	int getcwd_is_success = 0, chdir_return = 0;
	int path_is_home, path_is_previous;

	/* STEP 1: Save the OLDPWD */
	getcwd_is_success = getcwd(oldpwd, PATH_MAX) != NULL;
	if (!getcwd_is_success)
	{
		handle_cd_error(sh);
		return;
	}
	/* STEP 2: Change directory */
	path_is_home = path == NULL || _strcmp(path, "~") == 0;
	path_is_previous = _strcmp(path, "-") == 0;
	if (path_is_home)
		chdir_return = cd_home(path);
	else if (path_is_previous)
		chdir_return = cd_previous();
	else
		chdir_return = cd_path(path);
	if (chdir_return == -1)
	{
		handle_cd_error(sh);
		return;
	}
	/* STEP 3: Save the PWD */
	getcwd_is_success = getcwd(pwd, PATH_MAX) != NULL;
	if (!getcwd_is_success)
	{
		handle_cd_error(sh);
		return;
	}
	/* Print PWD, if "-" is used */
	if (!path_is_home && path_is_previous)
		_printf("%s\n", pwd);
	/* STEP 4: Update PWD and OLDPWD of the environment */
	_setenv("OLDPWD", oldpwd, sh);
	_setenv("PWD", pwd, sh);
	sh->exit_code = EXIT_SUCCESS;
}

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
