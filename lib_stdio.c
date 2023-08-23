#include "lib.h"

/**
 * _putchar - writes the character 'c' to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 *         On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
	return (write(1, &c, 1));
}

/**
 * _printf - implementation of printf function
 * @format: format string
 *
 * Return: number of characters printed, or -1 if there is an output error
 */
int _printf(const char *format, ...)
{
	int printed_chars = 0;
	va_list args;

	if (format == NULL ||
		_strcmp((char *)format, "%") == 0 ||
		_strcmp((char *)format, "% ") == 0)
		return (-1);
	va_start(args, format);
	printed_chars += _vdprintf(STDOUT_FILENO, format, args);
	va_end(args);
	return (printed_chars);
}

/**
 * _dprintf - implementation of dprintf function
 * @fd: file descriptor to write output to
 * @format: format string
 *
 * Return: number of characters printed, or -1 if there is an output error
 */
int _dprintf(int fd, const char *format, ...)
{
	int printed_chars = 0;
	va_list args;

	if (format == NULL ||
		_strcmp((char *)format, "%") == 0 ||
		_strcmp((char *)format, "% ") == 0 ||
		fd == -1)
		return (-1);
	va_start(args, format);
	printed_chars += _vdprintf(fd, format, args);
	va_end(args);
	return (printed_chars);
}

/**
 * _vdprintf - implementation of vdprintf function
 * @fd: file descriptor to write output to
 * @format: format string
 * @args: pointer to optional arguments provided
 *
 * Return: number of characters printed, or -1 if there is an output error
 */
int _vdprintf(int fd, const char *format, va_list args)
{
	char *ptr = (char *)format, *spc, fmt_buf[BUFFER_SIZE] = {0};
	int printed_chars = 0, fmt_case = 0, ctr = 0;
	int (*handle)(fmt_data_t *, char *, int *);
	fmt_data_t fdata;

	fdata.fd = fd;
	va_copy(fdata.args, args);
	while (*ptr != '\0')
		switch (fmt_case)
		{
		case NORMAL:
			if (*ptr == '%')
			{
				fmt_case = CONVERSION;
				break;
			}
			printed_chars += _putchar_buf(fdata.fd, *ptr, fmt_buf, &ctr);
			++ptr;
		break;
		case CONVERSION:
			fmt_case = NORMAL;
			initialize_format_data(&fdata);
			spc = get_specifier(ptr + 1, &fdata);
			if (spc != NULL) /* Valid format syntax */
			{
				handle = get_specifier_handler(*spc);
				printed_chars += handle(&fdata, fmt_buf, &ctr);
				ptr = spc + 1;
				break;
			}
			printed_chars += print_invalid_syntax(&ptr, &fdata, fmt_buf, &ctr);
		break;
		}
	printed_chars += _putchar_buf(fdata.fd, BUFFER_FLUSH, fmt_buf, &ctr);
	va_end(fdata.args);
	return (printed_chars);
}

