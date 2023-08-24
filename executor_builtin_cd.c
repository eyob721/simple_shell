#include "shell.h"

/**
 * execute_builtin_cd - executes the builtin command 'cd'
 * @sh: pointer to the shell data
 *
 * Return: void
 * Description: The function follows the following steps
 *     - STEP 1:- First get the OLDPWD path, which is the current directory
 *                path before changing directory.
 *     - STPE 2:- Change to the given directory.
 *     - STEP 3:- Then get the PWD path, which is the current directory path
 *                after changing directory.
 *              - Here the PWD must be printed, if the argument "-" is given.
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
	_setenv("OLDPWD", oldpwd, &sh->env_count);
	_setenv("PWD", pwd, &sh->env_count);
	sh->exit_code = EXIT_SUCCESS;
}
