#include "shell.h"

/**
 * main - a super simple shell program
 * @ac: argument count
 * @av: argument vector
 *
 * Return: 0 on success, or any other exit code based on the commands run
 */
int main(int ac, char **av)
{
	int fd = STDIN_FILENO, mode, bytes_read, line_size;
	char *line_buff = NULL, exit_code = 0;
	cmd_data_t cmd = {0, NULL, 0};

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			_dprintf(STDERR_FILENO, "File not found\n");
			return (1);
		}
	}
	mode = isatty(fd);
	do {
		if (mode == INTERACTIVE_MODE)
		{
			_printf("($) ");
			fflush(stdout);
		}
		bytes_read = read_line(fd, &line_buff, &line_size);
		if (bytes_read != READ_EOF && bytes_read != READ_ERR)
		{
			++cmd.cmd_line_no;
			cmd.cmd_argc = get_argument_count(line_buff);
			cmd.cmd_argv = get_argument_vector(line_buff, cmd.cmd_argc);
			exit_code = execute_binary(&cmd);
			free_string_array(cmd.cmd_argv, cmd.cmd_argc);
		}
	} while (bytes_read != READ_EOF && bytes_read != READ_ERR);
	free(line_buff);
	return (exit_code);
}

/**
 * execute_binary - an executor function for executing binary commands
 * @cmd: pointer to the command data
 *
 * Return: the exit code of the binary
 */
int execute_binary(cmd_data_t *cmd)
{
	int exit_code = 0, exec_status, child_status, child_exited_normally;
	pid_t pid;

	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid > 0)
		wait(&child_status);
	else if (pid == 0)
	{
		exec_status = execve(cmd->cmd_argv[0], cmd->cmd_argv, NULL);
		if (exec_status == -1)
		{
			_dprintf(STDERR_FILENO, "Error is executing the command\n");
			return (1);
		}
	}
	child_exited_normally = WIFEXITED(child_status);
	if (child_exited_normally)
		exit_code = WEXITSTATUS(child_status);
	return (exit_code);
}
