/*
 * ----------------------------------------------------------------------------
 *                          FINDING ARGUMENTS
 * ----------------------------------------------------------------------------
 *
 * The functions in these file are used to find the argument count and the
 * argument vector of a command. The function try to implement how the main
 * function gets arguments from the user.
 *			i.e. int main(int ac, char **av);
 *
 * So in these implementation the characters that end an argument are
 * considered to be:
 *		- a space(' '), &
 *		- a single quote or a double quote.
 *
 * What is considered an argument is generally a single word, which are
 * characters that come after a space, or start with a non-space character.
 * So word and argument are used to mean the same thing.
 *
 * What makes it a bit complicated is how quotations are handled in the
 * arguments. A word can begin with a quotation or any other character
 *
 * In the case where a word begins with a quotation, then everything inside
 * those quotation will count as one argument.
 *	e.g. the argument [echo "Hello World"],
 *       has two arguments -> [0]: echo
 *                         -> [1]: Hello World
 *
 * Now in the case where a word begins with a non-quotation character but has a
 * quotations in the middle of the word, then the start and the end quotes are
 * removed and everything inside of the quotes are considered to be part of the
 * argument.
 *	e.g. the argument [echo Hello"inside quotes"World]
 *       has two arguments -> [0]: echo
 *                         -> [1]: Helloinside quotesWorld
 *
 * Note that the starting and ending quotations are removed, if there are
 * quotations in an argument. Whatever case it might be.
 *
 * So to remove this quotes found in an argument, we can shift the characters
 * from right to left, from the quotes to the argument end (for both the
 * starting and ending quotes) and remove the quotes that way.
 *
 * But note that everything inside the starting and ending quotes stay as it is
 *	e.g. the argument [echo Hello"start 'single' end"World]
 *       has two arguments -> [0]: echo
 *                         -> [0]: Hellostart 'single' endWorld
 *
 * So to handle these different cases we used a state machine:
 *		- SPACE: In this state all spaces are skipped until a non-space
 *		         character is found. In which case it will go into the
 *		         ARGUMENT state.
 *		- ARGUMENT: In this state we find the end of the argument, and move
 *		            forward to the next argument.
 *		            In the function `get_argument_vector` quotes are removed by
 *		            shifting operation in the ARGUMENT state.
 *
 * WARNING: Quotations which are not closed have undefined behavior.
 *
 */

#include "shell.h"

/**
 * get_argument_count - get the number of arguments in a string
 * @str: a string
 *
 * Return: number of arguments
 */
int get_argument_count(char *str)
{
	int count = 0, state = SPACE;

	while (str != NULL && *str != '\0')
		switch (state)
		{
			case SPACE:
				while (*str == ' ')
					++str;
				state = ARGUMENT;
				break;
			case ARGUMENT:
				str = get_argument_end(str);
				++count;
				state = SPACE;
				break;
		}
	return (count);
}

/**
 * get_argument_vector - builds an array of arguments, form a given string
 * @str: a given string
 * @argc: argument count
 *
 * Return: array of arguments, or NULL if error occurs
 */
char **get_argument_vector(char *str, int argc)
{
	int i = 0, state = SPACE;
	char **argv = NULL, *arg_end;

	if (str == NULL || argc <= 0)
		return (NULL);
	argv = malloc(sizeof(char **) * (argc + 1)); /* +1  for NULL */
	if (argv == NULL)
		return (NULL);
	while (i < argc)
		switch (state)
		{
			case SPACE:
				while (*str == ' ')
					++str;
				state = ARGUMENT;
				break;
			case ARGUMENT:
				arg_end = get_argument_end(str);
				remove_quotations(str, &arg_end);
				*arg_end = '\0';
				argv[i] = _strdup(str);
				if (argv[i] == NULL)
				{
					free_string_array(argv, i);
					return (NULL);
				}
				++i;
				state = SPACE;
				str = arg_end + 1;
				break;
		}
	argv[argc] = NULL;
	return (argv);
}

/**
 * get_argument_end - used to find the end of an argument
 * @arg_start: pointer to the start of the argument
 *
 * Return: pointer to the end of the argument
 */
char *get_argument_end(char *arg_start)
{
	char *arg_end = NULL;
	char qt_char = 0, *quotes = "\'\"", *qt_start = NULL, *qt_end = NULL;
	int arg_has_quotes = 0;

	if (arg_start == NULL)
		return (NULL);
	arg_has_quotes = _strspn(arg_start, quotes) != 0;
	while (arg_has_quotes)
	{
		/* Find the start quote */
		qt_start = _strpbrk(arg_start, quotes);
		/* Save the quote character */
		qt_char = *qt_start;
		/* Find the end quote */
		qt_end = _strchr(++qt_start, qt_char);
		/* Move forward, if quotations is not closed then move to quote start */
		arg_start = qt_end != NULL ? ++qt_end : qt_start;
		/* Check for quotes */
		arg_has_quotes = _strspn(arg_start, quotes) != 0;
	}
	/* Find the argument end */
	arg_end = _strchr(arg_start, ' ');
	if (arg_end == NULL)
		arg_end = _strchr(arg_start, '\0');
	return (arg_end);
}

/**
 * remove_quotations - a function that remove the quotes found in an argument
 *					   by shifting characters.
 * @arg_start: pointer to the start of the argument
 * @arg_end: a double pointer to the end of the argument
 *
 * Return: void
 * Description: The function adjusts the argument end after each shifting
 */
void remove_quotations(char *arg_start, char **arg_end)
{
	char qt_char = 0, *quotes = "\'\"", *qt_start = NULL, *qt_end = NULL;

	if (arg_start == NULL || arg_end == NULL)
		return;
	while (_strspn(arg_start, quotes) != 0)
	{
		/* Find the quote start and end */
		qt_start = _strpbrk(arg_start, quotes);
		qt_char = *qt_start;
		qt_end = _strchr(++qt_start, qt_char);

		/* Shift the starting quote */
		while (qt_start <= *arg_end)
		{
			*(qt_start - 1) = *qt_start;
			++qt_start;
		}
		arg_start = qt_end != NULL ? qt_end : qt_start;
		--(*arg_end);

		/* Shift the ending quote, if there is one */
		if (qt_end != NULL)
		{
			while (qt_end <= *arg_end)
			{
				*(qt_end - 1) = *qt_end;
				++qt_end;
			}
			--(*arg_end);
		}
	}
}
