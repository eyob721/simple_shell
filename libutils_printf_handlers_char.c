#include "lib.h"

/**
 * handle_char - handler function for character conversion
 * @f: pointer to the format data
 * @buf: a pointer to the format buffer
 * @ctr: current index/counter in the buffer
 *
 * Return: number of characters printed to stdout
 */
int handle_char(fmt_data_t *f, char *buf, int *ctr)
{
	int len = 0, printed_chars = 0;
	char *chr_fmt, chr = va_arg(f->args, int);

	if (f->fmt_opts_set == 0) /* Check if formatting is required */
	{
		printed_chars += _putchar_buf(f->fd, chr, buf, ctr);
		return (printed_chars);
	}

	chr_fmt = format_character_output(&chr, &len, f);

	printed_chars += _puts_nbytes_buf(f->fd, chr_fmt, len, buf, ctr);
	free(chr_fmt);
	return (printed_chars);
}

/**
 * handle_string - handler function for string conversion
 * @f: pointer to the format data
 * @buf: a pointer to the format buffer
 * @ctr: current index/counter in the buffer
 *
 * Return: number of characters printed to stdout
 */
int handle_string(fmt_data_t *f, char *buf, int *ctr)
{
	int printed_chars = 0;
	char *str_fmt = NULL, *str = va_arg(f->args, char *);

	if (str == NULL)
		str = "(null)";

	if (f->fmt_opts_set == 0) /* Check if formatting is required */
	{
		printed_chars += _puts_buf(f->fd, str, buf, ctr);
		return (printed_chars);
	}

	str_fmt = format_character_output(str, NULL, f);

	printed_chars += _puts_buf(f->fd, str_fmt, buf, ctr);
	free(str_fmt);
	return (printed_chars);
}

/**
 * handle_percent - handler function for percent conversion
 * @f: pointer to the format data
 * @buf: a pointer to the format buffer
 * @ctr: current index/counter in the buffer
 *
 * Return: number of characters printed to stdout
 */
int handle_percent(fmt_data_t *f, char *buf, int *ctr)
{
	int printed_chars = 0;

	(void)f;
	printed_chars += _putchar_buf(f->fd, '%', buf, ctr);
	return (printed_chars);
}
