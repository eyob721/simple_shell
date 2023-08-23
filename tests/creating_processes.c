#include "../shell.h"

#define CHILD_EXIT_CODE 42


void child_process(pid_t pid);
void parent_process(pid_t pid, int child_status);
/**
 * main - test program for creating processes
 *
 * Return: 0 on success, or 1 on error
 */
int main(void)
{
	pid_t pid;
	int child_status;

	_printf("Before fork call, my pid is [%d].\n", getpid());
	_printf("Fork here.\n");
	pid = fork();

	if (pid == -1)
	{
		_dprintf(STDERR_FILENO, "Error is forking a process.\n");
		return (EXIT_FAILURE);
	}

	if (pid == 0)
		child_process(pid);
	else if (pid > 0)
	{
		wait(&child_status);
		parent_process(pid, child_status);
	}

	return (EXIT_SUCCESS);
}

void child_process(pid_t pid)
{
	_printf("Child: I am the child, my pid is [%d] and the fork return pid is [%d].\n", getpid(), pid);
	exit(CHILD_EXIT_CODE);
}

void parent_process(pid_t pid, int child_status)
{
	int child_exited_normally, child_exit_code;

	_printf("Parent: I am the parent, my pid is [%d] and the fork return pid is [%d].\n", getpid(), pid);

	child_exited_normally = WIFEXITED(child_status);

	if (child_exited_normally)
	{
		child_exit_code = WEXITSTATUS(child_status);
		_printf("Child exited normally\n");
		_printf("Child Exit Code: [%d]\n", child_exit_code);
		return;
	}
	_printf("Child did not exit normally\n");
}
