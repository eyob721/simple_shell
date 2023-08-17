/*
 * ----------------------------------------------------------------------------
 *								FORMATTING
 * ----------------------------------------------------------------------------
 *
 * Okay so basically formatting contains the following parts
 *			- converted string, (could be an integer type converted to a string,
 *			  a character cast to a string, or a string)
 *			- format length
 *			- padding character
 *			- justification
 *			- prefix (for integer conversions)
 *
 *	So the steps that are taken in formatting the given string are:
 *
 *	Step 1: Determine the format field length
 *		1.1: CHARACTER CONVERSIONS (character and string)
 *			- For character conversions the format field length is the maximum
 *			  of the two values below
 *					- width
 *					- length of the converted string
 *			- For string conversions, the precision is not used to determine
 *			  the length of the format field, but it tells us how many
 *			  characters from the string to put on that format field. So if the
 *			  precision given is less than the length of the given string then
 *			  the string must be truncated. Otherwise if the precision is
 *			  larger, then the string will written on the format field as-is.
 *		1.2: INTEGER CONVERSIONS (int, unsigned, octal, hex, and pointers)
 *			- For integer conversions the format field length is the maximum of
 *			  the three values below
 *					- width
 *					- precision
 *					- length of the converted string
 *			- For integer conversions, the precision is considered, because the
 *			  precision determines the minimum number of digits that are printed
 *			- So in the case where a precision is given that is larger than the
 *			  width and the length of the integer string, then the format field
 *			  length must take on the value of the precision, and extra spaces
 *			  must be padded to the left with zeros.
 *	Step 2: Determine the padding
 *			- The padding depends on the precision, the zero flag and the minus
 *			  flag.
 *			- The default padding character is a blank (' ').
 *			- The padding character, can be set to '0', if the precision is
 *			  specified, or if the zero is flag is set but the minus flag is not
 *			  set.
 *	Step 3: Determine the justification
 *			- The default justification is to the right
 *			- It can be set to the left, if the minus flag is set
 *	Step 4: Based on the format length we allocate memory
 *			- Handle malloc return, in case memory allocation fails
 *	Step 5: Write the converted string, on the allocated memory, based on the
 *			formatting options
 *		5.1: CHARACTER CONVERSIONS (character and string)
 *			- For character conversions, it is simple. There is no prefixes to
 *			  consider, and the only padding that is used is blank padding
 *			- In the case of empty strings, we dont print anything, but the null
 *			  character is counted, in the case of character conversion, but not
 *			  for string conversion.
 *			- That is why we pass the field length back to the handler functions
 *			  for character and strings, using pass by reference. Although the
 *			  string handler doesn't require it.
 *		5.2: INTEGER CONVERSIONS (int, unsigned, octal, hex, and pointers)
 *			- For all integer conversions (except for pointers), we have to take
 *			  care of prefixes
 *			- prefixes are signs ('+', '-', ' '), or number format indicators
 *			  ('0', '0x', '0X') that are written before the number
 *			- the prefixes are written differently based on the padding and
 *			  justification options used
 *
 *				Case: zero padding
 *						[prefix][padding][number]
 *
 *				e.g. -7284 -> with zero padding -> [-000007284]
 *
 *			- So justification will have no effect when zero padding is
 *			  used because the padding is put in the middle of the prefix and
 *			  the number, which pushes the prefix and the number to the field
 *			  ends.
 *			- And when blank padding is used, justification will be applied and
 *			  the syntax is as follows:
 *
 *				Case: blank padding
 *					left justify	[prefix][number][padding]
 *					right justify	[padding][prefix][number]
 *
 *				e.g. left justify:	[-7284      ]
 *					 right justify: [      -7284]
 *
 * So these are the formatting steps that are taken to implement printf
 *
 *
 * Hope this helps :)
 * ----------------------------------------------------------------------------
 */

#include "lib.h"

/**
 * format_character_output - used to format character and string conversions
 * @str: string to be formatted
 * @fmt_len: integer pointer, used to pass by reference the value of the format
 *			 length back to the handler function
 * @f: pointer to the format data
 *
 * Return: pointer to the formatted output, or NULL if memory allocation fails
 * Description:
 *		- For character formatting we need to send the value of the format
 *		  output length back to the handler function, so that we can print only
 *		  the first 'n' bytes of that length
 */
char *format_character_output(char *str, int *fmt_len, fmt_data_t *f)
{
	fmt_field_data_t fd;
	int precision_is_set;

	/* Initialize format output data */
	fd.fmt_field = NULL;
	fd.pre = "";
	fd.str = str;
	fd.str_len = _strlen(str);
	fd.pre_len = 0;
	fd.pad = ' ';
	fd.jst = 'r';

	/* Step 1: Determine format output length */
	precision_is_set = f->precision >= 0;
	/* Truncate 'str' if precision is set and is less than the length of 'str'*/
	if (precision_is_set && f->precision < fd.str_len)
		fd.str_len = f->precision;
	fd.field_len = MAX(fd.str_len, f->width);

	/* Step 2: Determine justification */
	if (f->minus_flag == 1)
		fd.jst = 'l';

	/* Step 3: Allocate memory for format output */
	fd.fmt_field = malloc(sizeof(char) * (fd.field_len + 1));
	if (fd.fmt_field == NULL)
		return (NULL);

	/* Step 4: Write format output */
	fd.fmt_field[fd.field_len] = '\0';
	_memset(fd.fmt_field, fd.pad, fd.field_len);
	write_character_format(&fd);
	if (fmt_len != NULL)
		*fmt_len = fd.field_len;
	return (fd.fmt_field);
}

/**
 * write_character_format - used to write the given string on the newly
 *							allocated format output, based on the formatting
 *							preferences (i.e. justification and padding)
 * @fd: pointer to the format field data
 *
 * Return: void
 * Description: In case of an empty string, it also must be printed on the
 *				format field.
 */
void write_character_format(fmt_field_data_t *fd)
{
	int str_pos;

	/* First determine the position of the string, on the format field */
	/**
	 * If the converted string is an empty string,
	 * then you must write the null byte and count it as well
	 */
	if (*(fd->str) == '\0')
	{
		fd->field_len = fd->field_len != 0 ? fd->field_len - 1 : 0;
		fd->fmt_field[fd->field_len] = '\0';
		fd->field_len++;
		return;
	}
	/* For default blank padding */
	switch (fd->jst)
	{
		case 'l':
			str_pos = 0;
		break;
		case 'r':
			str_pos = fd->field_len - fd->str_len;
		break;
	}
	/* Write string */
	_memcpy(fd->fmt_field + str_pos, fd->str, fd->str_len);
}

/**
 * format_integer_output - used to format all integer conversions, i.e. signed,
 *						   unsigned, octal, hexadecimal and pointers as well.
 * @str: the converted integer string
 * @prefix: prefix for the integer
 * @f: pointer to the format data
 *
 * Return: pointer to the formatted output, or NULL if memory allocation fails
 */
char *format_integer_output(char *str, char *prefix, fmt_data_t *f)
{
	fmt_field_data_t fd;
	int int_len, precision_is_set;

	/* Initialize format output data */
	fd.fmt_field = NULL;
	fd.str = str;
	fd.pre = prefix;
	fd.str_len = _strlen(str);
	fd.pre_len = _strlen(prefix);
	fd.pad = ' ';
	fd.jst = 'r';
	fd.prc = f->precision;

	/* Step 1: Determine format output length */
	int_len = fd.str_len + fd.pre_len;
	fd.field_len = MAX(int_len, MAX(f->width, f->precision));
	precision_is_set = fd.field_len == f->precision;
	if (precision_is_set)
		fd.field_len += fd.pre_len;

	/* Step 2: Determine padding  and justification */
	if (precision_is_set || (f->zero_flag == 1 && f->minus_flag == 0))
		fd.pad = '0';
	if (f->minus_flag == 1)
		fd.jst = 'l';

	/* Step 3: Allocate memory for format output */
	fd.fmt_field = malloc(sizeof(char) * (fd.field_len + 1));
	if (fd.fmt_field == NULL)
		return (NULL);

	/* Step 4: Write format output */
	fd.fmt_field[fd.field_len] = '\0';
	_memset(fd.fmt_field, fd.pad, fd.field_len);
	write_integer_format(&fd);
	return (fd.fmt_field);
}

/**
 * write_integer_format - used to write the given string on the newly allocated
 *						 format field, based on the formatting preferences
 *						 (i.e. justification and padding)
 * @fd: pointer to the format field data
 *
 * Return: void
 */
void write_integer_format(fmt_field_data_t *fd)
{
	int pre_pos, str_pos, prc_pos;

	/* First determine the positions of the prefix and integer string */
	if (fd->pad == '0') /* For zero padding */
	{
		pre_pos = 0;
		str_pos = fd->field_len - fd->str_len;
	}
	else
		switch (fd->jst) /* For default blank padding */
		{
			case 'l':
				pre_pos = 0;
				if (fd->prc > 0 && fd->prc > fd->str_len)
				{
					prc_pos = pre_pos + fd->pre_len; /* precision position */
					str_pos = prc_pos + (fd->prc - fd->str_len);
					/* pad extra spaces with zeros, to the left */
					_memset(fd->fmt_field + prc_pos, '0', fd->prc);
					break;
				}
				str_pos = fd->pre_len;
			break;
			case 'r':
				if (fd->prc > 0 && fd->prc > fd->str_len)
				{
					pre_pos = fd->field_len - (fd->pre_len + fd->prc);
					prc_pos = pre_pos + fd->pre_len; /* precision position */
					str_pos = prc_pos + (fd->prc - fd->str_len);
					/* pad extra spaces with zeros, to the left */
					_memset(fd->fmt_field + prc_pos, '0', fd->prc);
					break;
				}
				pre_pos = fd->field_len - (fd->pre_len + fd->str_len);
				str_pos = fd->field_len - fd->str_len;
			break;
		}
	/* Write prefix and integer string */
	_memcpy(fd->fmt_field + pre_pos, fd->pre, fd->pre_len);
	_memcpy(fd->fmt_field + str_pos, fd->str, fd->str_len);
}

