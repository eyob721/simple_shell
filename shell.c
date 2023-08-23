#include "shell.h"

/**
 * main - a simple shell program
 * @ac: argument count
 * @av: argument vector
 *
 * Return: depends on the exit code of the last command run
 */
int main(int __attribute__((unused)) ac, char __attribute__((unused)) * *av)
{
	int fd = STDIN_FILENO, mode, bytes_read;
	void (*execute_cmd)(shell_t *cmd) = NULL;
	shell_t shell;

	initialize_shell_data(&shell, av);
	mode = isatty(fd);
	do
	{
		if (mode == INTERACTIVE_MODE)
		{
			write(STDOUT_FILENO, "($) ", 5);
			fflush(stdout);
		}
		bytes_read = read_line(fd, &shell.line_buff, &shell.line_size);
		if (bytes_read != READ_EOF && bytes_read != READ_ERR)
		{
			++shell.line_no;
			shell.cmd_ac = get_argument_count(shell.line_buff);
			shell.cmd_av = get_argument_vector(shell.line_buff, shell.cmd_ac);
			if (shell.cmd_av == NULL) /* Empty command */
				continue;
			execute_cmd = get_executor(shell.cmd_av[0]);
			if (execute_cmd != NULL)
				execute_cmd(&shell);
			free_string_array(shell.cmd_av, shell.cmd_ac);
		}
	} while (bytes_read != READ_EOF && bytes_read != READ_ERR);
	if (bytes_read == READ_EOF && mode == INTERACTIVE_MODE)
		_putchar('\n');
	free(shell.line_buff);
	free_environ(shell.env_cur_start);
	return (shell.exit_code);
}

/**
 * initialize_shell_data - initializes shell data at program startup
 * @sh: pointer to the shell data
 * @av: argument vector of the shell program
 *
 * Return: void
 */
void initialize_shell_data(shell_t *sh, char **av)
{
	sh->prg_name = *av;
	sh->line_buff = NULL;
	sh->line_size = 0;
	sh->line_no = 0;
	sh->cmd_ac = 0;
	sh->cmd_av = NULL;
	sh->exit_code = EXIT_SUCCESS;

	/* Environment Initialization */
	sh->env_count = get_environ_count();
	environ = get_environ_copy(sh->env_count);
	sh->env_cur_start = sh->env_cur_end = environ + sh->env_count;
}

/**
 * get_executor - a function used to fetch the right executor function for a
 *                given command
 * @given_cmd: a given command string
 *
 * Return: pointer to an executor function
 */
void (*get_executor(char *given_cmd))(shell_t *sh)
{
	executor_t cmd_exec[] = {
		{"exit", execute_builtin_exit},
		{"env", execute_builtin_env},
		{"unsetenv", execute_builtin_unsetenv},
		{"setenv", execute_builtin_setenv},
		{"cd", execute_builtin_cd},
		{NULL, execute_system}};
	int i = 0;

	if (given_cmd == NULL)
		return (NULL);
	while (cmd_exec[i].cmd != NULL)
	{
		if (_strcmp(cmd_exec[i].cmd, given_cmd) == 0)
			break;
		++i;
	}
	return (cmd_exec[i].executor);
}
