#include "shell.h"

/**
 * print_alias_list - prints all the elements of the alias list
 * @head: pointer to the head of the alias list
 *
 * Return: void
 */
void print_alias_list(alias_t *head)
{
	while (head != NULL)
	{
		_printf("%s='%s'\n", head->alias_name, head->real_name);
		head = head->next;
	}
}

/**
 * print_alias_node - finds and prints a node with a given alias name
 * @head: pointer to the head of the alias list
 * @given_name: given alias name
 *
 * Return: 0 on success, or 1 on error
 */
int print_alias_node(alias_t *head, char *given_name)
{
	alias_t *node = NULL;

	node = search_alias_list(head, given_name);
	if (node != NULL)
	{
		_printf("%s='%s'\n", node->alias_name, node->real_name);
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

/**
 * add_alias_node - a function that adds a new node at
 *					the beginning of the alias list.
 * @head: a double pointer to the head of the alias list
 * @tail: a double pointer to the tail of the alias list
 * @node: the alias argument to be the new node in the list
 *
 * Return: 0 on success, or 1 on error
 */
int add_alias_node(alias_t **head, alias_t **tail, char *node)
{
	alias_t *new_alias = NULL;
	char *alias_name = NULL, *real_name = NULL, *equal_sign = NULL;

	if (head == NULL || tail == NULL || node == NULL)
		return (EXIT_FAILURE);
	alias_name = node;
	equal_sign = _strchr(node, '=');
	real_name = equal_sign + 1;
	*equal_sign = '\0';
	/* If the alias already exists, update the real value */
	new_alias = search_alias_list(*head, alias_name);
	if (new_alias != NULL)
	{
		free(new_alias->real_name);
		new_alias->real_name = _strdup(real_name);
		if (new_alias->real_name == NULL)
			return (EXIT_FAILURE);
		return (EXIT_SUCCESS);
	}
	/* If the alias doesn't exist, then build the new alias node */
	new_alias = malloc(sizeof(alias_t));
	if (new_alias == NULL)
		return (EXIT_FAILURE);
	new_alias->alias_name = _strdup(alias_name);
	new_alias->real_name = _strdup(real_name);
	new_alias->next = NULL;
	/* Add node to the alias list */
	if (*head == NULL)
		*head = new_alias;
	else
		(*tail)->next = new_alias;
	*tail = new_alias;
	return (EXIT_SUCCESS);
}

/**
 * search_alias_list - searches for a node with the given alias name.
 * @head: head of the alias list
 * @given_name: given alias name to search for
 *
 * Return: pointer to the node if it is found, NULL otherwise.
 */
alias_t *search_alias_list(alias_t *head, char *given_name)
{
	while (head != NULL)
	{
		if (_strcmp(head->alias_name, given_name) == 0)
			return (head);
		head = head->next;
	}
	return (NULL);
}

/**
 * substitute_alias_cmd - a function that substitutes a command with the real
 *                        command, if it is an alias.
 * @head: head of the alias list
 * @cmd: command
 *
 * Return: pointer to the substituted command.
 */
char *substitute_alias_cmd(alias_t *head, char *cmd)
{
	alias_t *cmd_alias = NULL;
	char *cmd_name = NULL, *cmd_args = NULL, *cmd_cpy = NULL;

	/* Make a copy */
	cmd_cpy = _strdup(cmd);
	if (cmd_cpy == NULL)
		return (cmd);

	/* Get the command name, which the first argument/word of the command */
	cmd_name = _strtok_r(cmd, " \t", &cmd_args);

	/* Check if the command name is an alias */
	cmd_alias = search_alias_list(head, cmd_name);

	/* If an alias is found, replace the cmd name with the real name */
	/* Also take care of recursive aliases */
	while (cmd_alias != NULL)
	{
		free(cmd_cpy);
		cmd_cpy = concat_strings(3, cmd_alias->real_name, " ", cmd_args);
		cmd_alias = search_alias_list(head, cmd_alias->real_name);
	}
	return (cmd_cpy);
}
