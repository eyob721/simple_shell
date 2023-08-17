#include "lib.h"

/**
 * _putchar_buf - a function that writes a character to the format buffer
 * @fd: file descriptor
 * @c: a character
 * @buf: a pointer to the format buffer
 * @ctr: current index/counter in the buffer
 *
 * Return: number of characters printed
 * Description: when a buffer flush signal is sent, or when the counter of the
 *				format buffer reaches the last index (i.e. BUFFER_SIZE - 1, or
 *				1024 - 1) it will write the contents of the buffer to stdout and
 *				resets the counter to 0
 */
int _putchar_buf(int fd, char c, char *buf, int *ctr)
{
	int printed_chars = 0;

	if (c == BUFFER_FLUSH || *ctr == BUFFER_SIZE - 2)
	{
		printed_chars += write(fd, buf, *ctr);
		*ctr = 0;
	}
	if (c != BUFFER_FLUSH)
		buf[(*ctr)++] = c;
	return (printed_chars);
}

/**
 * _puts_buf - a function that writes a string to the format buffer
 * @fd: file descriptor
 * @str: a string
 * @buf: a pointer to the format buffer
 * @ctr: current index/counter in the buffer
 *
 * Return: number of characters printed
 */
int _puts_buf(int fd, char *str, char *buf, int *ctr)
{
	int printed_chars = 0;

	while (str != NULL && *str != '\0')
		printed_chars += _putchar_buf(fd, *(str++), buf, ctr);
	return (printed_chars);
}

/**
 * _puts_nbytes_buf - a function that writes 'n' bytes from a given string to
 *					  the format buffer
 * @fd: file descriptor
 * @str: a string
 * @n: number of bytes to write
 * @buf: a pointer to the format buffer
 * @ctr: current index/counter in the buffer
 *
 * Return: number of characters printed
 */
int _puts_nbytes_buf(int fd, char *str, int n, char *buf, int *ctr)
{
	int printed_chars = 0, i = 0;

	while (str != NULL && i < n)
		printed_chars += _putchar_buf(fd, str[i++], buf, ctr);
	return (printed_chars);
}

