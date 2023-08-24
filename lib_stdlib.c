#include "lib.h"

/**
 * _abs - computes the absolute value of an integer
 * @x: an integer
 *
 * Return: the absolute value of x
 */
int _abs(int x)
{
	if (x < 0)
		return (-x);
	return (x);
}

/**
 * _atoi - converts a string into an integer
 * @s: a string
 *
 * Return: an integer
 */
int _atoi(char *s)
{
	unsigned int i, sign = 1, num = 0;

	if (s == NULL)
		return (0);
	/**
	 * Search for a number in the string
	 * Look for negative signs along the way
	 */
	for (i = 0; s[i] != '\0'; i++)
		if (s[i] == '-')
			sign *= -1;
		else if (_isdigit(s[i]))
			break;
	/* If there are no numbers return 0 */
	if (s[i] == '\0')
		return (0);
	/* If there are numbers then return the number */
	while (_isdigit(s[i]))
		num = (s[i++] - '0') + num * 10;
	/**
	 * NOTE: unsigned type is used to prevent errors for INT_MIN (-214748360)
	 * When INT_MIN is used, in the above loop the last expression will be
	 * 2147483640 + 8 -> which will cause overflow
	 */
	return (num * sign);
}

/**
 * _itoa - converts an integer to a string
 * @n: integer to be converted
 *
 * Return: string of n, or NULL otherwise
 */
char *_itoa(int n)
{
	int i, digits = 1, temp = n, is_neg = 0;
	char *num = NULL;

	for (temp /= 10; temp; temp /= 10)
		digits++;
	is_neg = n < 0 ? 1 : 0;
	if (is_neg)
		digits++;
	num = malloc(sizeof(char) * digits + 1); /* +1 for null byte */
	if (num == NULL)
		return (NULL);
	_memset(num, '\0', digits + 1); /* initialize heap allocation */
	for (temp = n, i = digits - 1; i >= 0; i--, temp /= 10)
		num[i] = (temp % 10) + '0';
	if (is_neg)
		num[0] = '-';
	return (num);
}

/**
 * _realloc - a function that reallocates a memory block using malloc and free
 * @ptr: pointer to the memory previously allocated with a call to malloc
 * @old_size: is the size in bytes, of the allocated space for ptr
 * @new_size: is the new size, in bytes of the new memory block
 *
 * Return:
 *		- newly allocated memory if successful.
 *		- NULL, if ptr is NULL & new_size is 0, or if memory allocation fails.
 * Description:
 *		- newly allocated memory is initialized to prevent memory errors.
 *		- contents of the old memory (ptr) is copied to the new memory.
 *		- if ptr is NULL, and new_size is not 0, then the call is equivalent
 *		  to malloc(new_size).
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	unsigned int i, min_size;
	char *new_mem = NULL;

	/**
	 * if ptr is not NULL and new_size is 0, then
	 * the call is equivalent to free(ptr)
	 */
	if (ptr != NULL && new_size == 0)
	{
		free(ptr);
		return (NULL);
	}

	/* if old_size == new_size, then no new memory allocation is required */
	if (old_size == new_size)
		return (ptr);

	/* Allocate new memory */
	new_mem = malloc(new_size);
	if (new_mem == NULL)
		return (ptr);

	/* Initialize new memory */
	_memset(new_mem, 0, new_size);

	/* Copy contents of old memory to new memory and free old memory */
	if (ptr != NULL)
	{
		min_size = old_size < new_size ? old_size : new_size;
		for (i = 0; i < min_size; i++)
			new_mem[i] = *((char *)ptr + i);
		free(ptr);
	}

	return ((void *)new_mem);
}

