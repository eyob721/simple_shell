#include "shell.h"

/**
 * main - a simple shell program
 * @ac: argument count
 * @av: argument vector
 *
 * Return: depends on the exit code of the last command run
 */
int main(int __attribute__((unused)) ac, char __attribute__((unused)) **av)
{
	int fd = STDIN_FILENO, mode, bytes_read;
	shell_t shell;

	initialize_shell_data(&shell, av);
	if (ac >= 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			_dprintf(STDERR_FILENO, "%s: %d: Can't open %s\n",
					shell.prg_name, shell.line_no, av[1]);
			shell.exit_code = CMD_NOT_FOUND;
			free_environ();
			return (shell.exit_code);
		}
	}
	mode = isatty(fd);
	do {
		if (mode == INTERACTIVE_MODE)
		{
			write(STDOUT_FILENO, "($) ", 5);
			fflush(stdout);
		}
		bytes_read = read_line(fd, &shell.line_buff, &shell.line_size);
		if (bytes_read != READ_EOF && bytes_read != READ_ERR)
		{
			++shell.line_no;
			execute_commands(&shell);
		}
	} while (bytes_read != READ_EOF && bytes_read != READ_ERR);
	if (bytes_read == READ_EOF && mode == INTERACTIVE_MODE)
		_putchar('\n');
	free(shell.line_buff);
	free_environ();
	free_alias_list(shell.alias_head);
	if (ac >= 2)
		close(fd);
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

	/* Alias Initialization */
	sh->alias_head = NULL;
	sh->alias_tail = NULL;
}

/**
 * execute_commands - executes commands found in the command line
 * @sh: pointer to the shell data
 *
 * Return: void
 */
void execute_commands(shell_t *sh)
{
	void (*execute)(shell_t *cmd) = NULL;
	char *cmd, *next_cmd = NULL, next_opr = '\0';

	sh->line_buff = remove_comments(sh->line_buff);
	cmd = cmd_tok(sh->line_buff, &next_cmd, &next_opr);
	while (cmd != NULL)
	{
		cmd = substitute_alias_cmd(sh->alias_head, cmd);
		cmd = expand_variables(sh->exit_code, cmd);
		sh->cmd_ac = get_argument_count(cmd);
		sh->cmd_av = get_argument_vector(cmd, sh->cmd_ac);
		free(cmd);
		execute = get_executor(sh->cmd_av[0]);
		execute(sh);
		free_string_array(sh->cmd_av, sh->cmd_ac);
		if (next_opr == '&' && sh->exit_code != EXIT_SUCCESS)
			break;
		else if (next_opr == '|' && sh->exit_code == EXIT_SUCCESS)
			break;
		cmd = cmd_tok(NULL, &next_cmd, &next_opr);
	}
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
		{"alias", execute_builtin_alias},
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
