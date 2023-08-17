#include "lib.h"

/**
 * handle_integer - handler function for signed integer conversion
 * @f: pointer to the format data
 * @buf: a pointer to the format buffer
 * @ctr: current index/counter in the buffer
 *
 * Return: number of characters printed to stdout
 */
int handle_integer(fmt_data_t *f, char *buf, int *ctr)
{
	int printed_chars = 0;
	long int num;
	char *int_fmt, prefix[2] = {0};
	char *int_str, int_buf[INT_BUF_SIZE] = "####################";

	if (f->modifier == 'h')
		num = (short)va_arg(f->args, int);
	else if (f->modifier == 'l')
		num = va_arg(f->args, long int);
	else
		num = (int)va_arg(f->args, int);

	if (num < 0)
		*prefix = '-';
	else if (f->plus_flag == 1 && num >= 0)
		*prefix = '+';
	else if (f->blank_flag == 1 && num >= 0)
		*prefix = ' ';

	/* If both precision and num are zero, then no need for formatting */
	if (f->precision == 0 && num == 0)
		int_str = "";
	else
		int_str = convert_int_to_str(num, int_buf, INT_BUF_SIZE);

	if (f->fmt_opts_set == 0) /* Check if formatting is required */
	{
		if (*prefix == '-')
			printed_chars += _putchar_buf(f->fd, *prefix, buf, ctr);
		printed_chars += _puts_buf(f->fd, int_str, buf, ctr);
		return (printed_chars);
	}

	int_fmt = format_integer_output(int_str, prefix, f);

	printed_chars += _puts_buf(f->fd, int_fmt, buf, ctr);

	free(int_fmt);
	return (printed_chars);
}

/**
 * handle_unsigned - handler function for unsigned conversion
 * @f: pointer to the format data
 * @buf: a pointer to the format buffer
 * @ctr: current index/counter in the buffer
 *
 * Return: number of characters printed to stdout
 */
int handle_unsigned(fmt_data_t *f, char *buf, int *ctr)
{
	int printed_chars = 0;
	unsigned long int num;
	char *uint_fmt;
	char *uint_str, uint_buf[UINT_BUF_SIZE] = "#####################";

	if (f->modifier == 'h')
		num = (unsigned short)va_arg(f->args, unsigned int);
	else if (f->modifier == 'l')
		num = va_arg(f->args, unsigned long int);
	else
		num = (unsigned int)va_arg(f->args, unsigned int);

	/* If both precision and num are zero, then you do nothing */
	if (f->precision == 0 && num == 0)
		uint_str = "";
	else
		uint_str = convert_uint_to_base_str(10, num, 'l', uint_buf, UINT_BUF_SIZE);

	if (f->fmt_opts_set == 0) /* Check if formatting is required */
	{
		printed_chars += _puts_buf(f->fd, uint_str, buf, ctr);
		return (printed_chars);
	}

	uint_fmt = format_integer_output(uint_str, "", f);

	printed_chars += _puts_buf(f->fd, uint_fmt, buf, ctr);
	free(uint_fmt);
	return (printed_chars);
}

/**
 * handle_octal - handler function for octal conversion
 * @f: pointer to the format data
 * @buf: a pointer to the format buffer
 * @ctr: current index/counter in the buffer
 *
 * Return: number of characters printed to stdout
 */
int handle_octal(fmt_data_t *f, char *buf, int *ctr)
{
	int printed_chars = 0;
	unsigned long int num;
	char *oct_fmt, prefix[2] = {0};
	char *oct_str, oct_buf[OCT_BUF_SIZE] = "#######################";

	if (f->modifier == 'h')
		num = (unsigned short)va_arg(f->args, unsigned int);
	else if (f->modifier == 'l')
		num = va_arg(f->args, unsigned long int);
	else
		num = (unsigned int)va_arg(f->args, unsigned int);

	if (f->hash_flag == 1 && num != 0)
		*prefix = '0';

	/* If both precision and num are zero, then you do nothing */
	if (f->precision == 0 && num == 0)
		oct_str = "";
	else
		oct_str = convert_uint_to_base_str(8, num, 'l', oct_buf, OCT_BUF_SIZE);

	if (f->fmt_opts_set == 0) /* Check if formatting is required */
	{
		printed_chars += _puts_buf(f->fd, oct_str, buf, ctr);
		return (printed_chars);
	}

	oct_fmt = format_integer_output(oct_str, prefix, f);

	printed_chars += _puts_buf(f->fd, oct_fmt, buf, ctr);
	free(oct_fmt);
	return (printed_chars);
}

/**
 * handle_hexadecimal- handler function for hexadecimal conversion
 * @f: pointer to the format data
 * @buf: a pointer to the format buffer
 * @ctr: current index/counter in the buffer
 *
 * Return: number of characters printed to stdout
 * Description:
 *		- In selecting the letter case,
 *			'l' is for lowercase letter case
 *			'C' is for Capital letter case
 */
int handle_hexadecimal(fmt_data_t *f, char *buf, int *ctr)
{
	int printed_chars = 0;
	unsigned long int num;
	char *hex_fmt, prefix[3] = "0x", ltr = f->spc_chr == 'x' ? 'l' : 'C';
	char *hex_str, hex_buf[HEX_BUF_SIZE] = "#################";

	if (f->modifier == 'h')
		num = (unsigned short)va_arg(f->args, unsigned int);
	else if (f->modifier == 'l')
		num = va_arg(f->args, unsigned long int);
	else
		num = (unsigned int)va_arg(f->args, unsigned int);

	if (f->spc_chr == 'X' && f->hash_flag == 1)
		prefix[1] = 'X';
	else if (f->hash_flag == 0 || num == 0)
		prefix[0] = '\0';

	/* If both precision and num are zero, then you do nothing */
	if (f->precision == 0 && num == 0)
		hex_str = "";
	else
		hex_str = convert_uint_to_base_str(16, num, ltr, hex_buf, HEX_BUF_SIZE);

	if (f->fmt_opts_set == 0) /* Check if formatting is required */
	{
		printed_chars += _puts_buf(f->fd, hex_str, buf, ctr);
		return (printed_chars);
	}

	hex_fmt = format_integer_output(hex_str, prefix, f);

	printed_chars += _puts_buf(f->fd, hex_fmt, buf, ctr);
	free(hex_fmt);
	return (printed_chars);
}

/**
 * handle_pointer - handler function for pointer conversion
 * @f: pointer to the format data
 * @buf: a pointer to the format buffer
 * @ctr: current index/counter in the buffer
 *
 * Return: number of characters printed to stdout
 */
int handle_pointer(fmt_data_t *f, char *buf, int *ctr)
{
	int printed_chars = 0;
	char *ptr_fmt;
	char *ptr_str, ptr_buf[PTR_BUF_SIZE] = "################";
	void *addr = va_arg(f->args, void *);

	if (addr == NULL)
		ptr_str = "(nil)";
	else
		ptr_str = convert_addr_to_hex_str(addr, ptr_buf, PTR_BUF_SIZE);

	if (f->fmt_opts_set == 0) /* Check if formatting is required */
	{
		printed_chars += _puts_buf(f->fd, ptr_str, buf, ctr);
		return (printed_chars);
	}

	ptr_fmt = format_integer_output(ptr_str, "", f);
	printed_chars += _puts_buf(f->fd, ptr_fmt, buf, ctr);
	free(ptr_fmt);
	return (printed_chars);
}
