#include "lib.h"

/**
 * _memset - fills the first n bytes of memory pointed by s
 * with a constant byte b
 * @s: memory location
 * @n: number of bytes
 * @b: a constant byte
 *
 * Return: memory area s
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; s != NULL && i < n; i++)
		s[i] = b;

	return (s);
}

/**
 * _memcpy - copies n bytes from memory area src to memory area dest
 * @dest: destination memory area
 * @src: source memory area
 * @n: number of bytes
 *
 * Return: destination memory area
 */
char *_memcpy(char *dest, char *src, unsigned int n)
{
	unsigned int i;

	if (dest != NULL && src != NULL)
		for (i = 0; i < n; i++)
			dest[i] = src[i];
	return (dest);
}

/**
 * _strlen - returns the length of a string
 * @s: a string
 *
 * Return: length of the string
 */
int _strlen(char *s)
{
	int len = 0;

	while (s != NULL && *(s++) != '\0')
		len++;
	return (len);
}

/**
 * _strcmp - compares two strings
 * @s1: first string
 * @s2: second string
 *
 * Return: less than, greater than or equal to zero
 */
int _strcmp(char *s1, char *s2)
{
	if (s1 != NULL && s2 != NULL)
	{
		while (*s1 != '\0' || *s2 != '\0')
		{
			if (*s1 != *s2)
				return (*s1 - *s2);
			++s1, ++s2;
		}
	}
	return (0);
}
/**
 * _strncmp - compares at most `n` bytes of two strings
 * @s1: first string
 * @s2: second string
 * @n: number of bytes to compare
 *
 * Return: less than, greater than or equal to zero
 */
int _strncmp(char *s1, char *s2, int n)
{
	int i = 0;

	if (s1 != NULL && s2 != NULL && n > 0)
	{
		while ((*s1 != '\0' || *s2 != '\0') && i < n)
		{
			if (*s1 != *s2)
				return (*s1 - *s2);
			++s1, ++s2, ++i;
		}
	}
	return (0);
}


