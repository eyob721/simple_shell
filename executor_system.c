#include "shell.h"

/**
 * execute_system - executes system commands
 * @sh: pointer to the shell data
 *
 * Return: void
 */
void execute_system(shell_t *sh)
{
	int child_status, cmd_execution_fails;
	char *full_path = NULL;
	pid_t pid;

	full_path = _which(sh->cmd_av[0]);
	if (full_path == NULL) /* command does not exist */
	{
		_dprintf(STDERR_FILENO, "%s: %d: %s: not found\n",
				sh->prg_name, sh->line_no, sh->cmd_av[0]);
		sh->exit_code = CMD_NOT_FOUND;
		return;
	}
	pid = fork();
	if (pid == -1) /* Fork fails */
	{
		perror(sh->cmd_av[0]);
		sh->exit_code = EXIT_FAILURE;
		return;
	}
	if (pid == 0) /* Child process */
	{
		cmd_execution_fails = execve(full_path, sh->cmd_av, environ) < 0;
		if (cmd_execution_fails)
		{
			perror(sh->cmd_av[0]);
			exit(EXIT_FAILURE); /* Exit from the child process */
		}
	}
	else if (pid > 0) /* Parent process */
	{
		wait(&child_status);
		free(full_path);
		sh->exit_code = WEXITSTATUS(child_status); /* Exit code of the child */
	}
}
