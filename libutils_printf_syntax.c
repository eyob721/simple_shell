#include "lib.h"

/**
 * check_flag - checks if the current character at the position pointed by 's'
 *				in the format string is a flag character
 * @s: double pointer to a position on the format string
 * @f: pointer to the format data
 *
 * Return: void
 * Description: The function checks if the current character at position 's' in
 *				the format string is a flag, and if it is it will set the
 *				appropriate flag and advances the 's' pointer to the next
 *				character in the format string. If the character at 's' is not
 *				a flag then the function will do nothing and exit.
 */
void check_flag(char **s, fmt_data_t *f)
{
	while (**s != '\0')
	{
		switch (**s)
		{
		case '-':
			f->minus_flag = 1;
		break;
		case '+':
			f->plus_flag = 1;
		break;
		case '0':
			f->zero_flag = 1;
		break;
		case '#':
			f->hash_flag = 1;
		break;
		case ' ':
			f->blank_flag = 1;
		break;
		default:
			return;
		}
		++(*s);
	}
}

/**
 * check_width - checks if the current character at the position pointed by 's'
 *				 in the format string is a width
 * @s: double pointer to a position on the format string
 * @f: pointer to the format data
 *
 * Return: void
 * Description: The function checks if the current character at position 's' in
 *				the format string is a width, and if it is it will set the
 *				value of width option to the given value in the format string
 *				and in doing so also advancing 's' to the next character until
 *				there are no more digits. But if the character at 's' is not
 *				width then the function will do nothing and exit.
 */
void check_width(char **s, fmt_data_t *f)
{
	f->width = 0;
	if (**s == '*')
	{
		f->width = va_arg(f->args, int);
		++(*s);
		return;
	}
	while (**s != '\0')
	{
		if (_isdigit(**s))
		{
			f->width = (f->width * 10) + (**s) - '0';
			++(*s);
			continue;
		}
		return;
	}
}

/**
 * check_precision - checks if the current character at the position pointed by
 *					 's' in the format string is a precision
 * @s: double pointer to a position on the format string
 * @f: pointer to the format data
 *
 * Return: void
 * Description: The function checks if the current character at position 's' in
 *				the format string is a precision (i.e. a dot(.) sign followed
 *				by numbers), and if it is it will set the value of precision
 *				option to the given value in the format string and in doing so
 *				also advancing 's' to the next character until there are no
 *				more digits. But if the character at 's' is not precision then
 *				function will do nothing and exit.
 */
void check_precision(char **s, fmt_data_t *f)
{
	if (**s != '.' && !(_isdigit(*(*s + 1))))
		return;
	++(*s);
	f->precision = 0;
	if (**s == '*')
	{
		f->precision = va_arg(f->args, int);
		++(*s);
		return;
	}
	while (**s != '\0')
	{
		if (_isdigit(**s))
		{
			f->precision = (f->precision * 10) + (**s) - '0';
			++(*s);
			continue;
		}
		return;
	}
}

/**
 * check_modifier - checks if the current character at the position pointed by
 *					's' in the format string is a modifier
 * @s: double pointer to a position on the format string
 * @f: pointer to the format data
 *
 * Return: void
 * Description: The function checks if the current character at position 's' in
 *				the format string is a modifier, and if it is it will set the
 *				value of modifier option to the given value in the format string
 *				and then it advances 's' to the next character. But if the
 *				character at 's' is not a modifier then function will do
 *				nothing and exit.
 */
void check_modifier(char **s, fmt_data_t *f)
{
	switch (**s)
	{
	case 'h':
		f->modifier = 'h';
	break;
	case 'l':
		f->modifier = 'l';
	break;
	default:
		return;
	}
	++(*s);
}

/**
 * check_specifier - checks if the current character at the position pointed by
 *					 's' in the format string is a specifier, and stores the
 *					 specifier character in the format data data
 * @s: double pointer to a position on the format string
 * @f: pointer to the format data
 *
 * Return: void
 * Description: The function checks if the current character at position 's' in
 *				the format string is a specifier. Now at this point the position
 *				pointer 's' must be at the conversion specifier character, if it
 *				is not then the format data in the format string are not set
 *				in the correct format syntax, make the format invalid so
 *				's' will be set to NULL. But if the character at 's' is a
 *				conversion specifier then it is a valid format syntax and so 's'
 *				will not be changed.
 *				NOTE: it is this final position 's' (NULL for invalid syntax or
 *				not NULL for valid syntax) that the function get_specifier()
 *				returns back to _printf()
 */
void check_specifier(char **s, fmt_data_t *f)
{
	char specifiers[] = "csdiuoxXp%";

	if (**s == '\0' || _strchr(specifiers, **s) == NULL)
	{
		f->invalid_spc = *s; /* Save the invalid specifier position */
		f->spc_chr = 0;
		*s = NULL;
		return;
	}
	f->spc_chr = **s;
	f->invalid_spc = NULL;
}
