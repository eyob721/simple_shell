#include <stdio.h>
#include <unistd.h>

/**
 * main - execve example
 *
 * Return: Always 0.
 */
int main(void)
{
    char *argv[] = {"./wrong",  NULL};
	int exec_stat;

    printf("Before execve\n");

	exec_stat = execve(argv[0], argv, NULL);

    if (exec_stat == -1)
    {
        perror("Error:");
    }
    printf("After execve\n");
    return (0);
}
