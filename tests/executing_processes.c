#include "../shell.h"

/**
 * main - test program for executing a command in a child process
 *
 * Return: 0 on sucess, or 1 on error
 */
int main(void)
{
	char *argv[] = {"/bin/ls", "-la", "/tmp", NULL};
	int i = 0, child_status, exec_status;
	pid_t pid;
	int child_exited_normally, child_exit_code;


	while (i++ < 5)
	{
		pid = fork();

		if (pid == -1)
		{
			_dprintf(STDERR_FILENO, "Error forking the current process\n");
			return (EXIT_FAILURE);
		}
		if (pid == 0)
		{
			exec_status = execve("/bin/ls", argv, NULL);
			if (exec_status == -1)
			{
				_dprintf(STDERR_FILENO, "Error is executing a command\n");
				return (EXIT_FAILURE);
			}
		}
		else if (pid > 0)
		{
			wait(&child_status);
			child_exited_normally = WIFEXITED(child_status);

			if (child_exited_normally)
			{
				child_exit_code = WEXITSTATUS(child_status);
				_printf("\n[EXIT CODE]: [%d]\n", child_exit_code);
			}
		}
	}
	return (EXIT_SUCCESS);
}
