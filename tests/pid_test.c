#include "../shell.h"
#include <unistd.h>

/**
 * main - a program that displays the PID of the current and parent process
 *
 * Return: 0 on success, or 1 on error
 */
int main(void)
{
	int pid = getpid();
	int ppid = getppid();

	_printf("PID: [%d]\n", pid);
	_printf("PPID: [%d]\n", ppid);
	return (0);
}
