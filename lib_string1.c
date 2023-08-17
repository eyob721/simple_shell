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
		while (*s1 != '\0' || *s2 != '\0')
		{
			if (*s1 != *s2)
				return (*s1 - *s2);
			s1++, s2++;
		}
	return (0);
}

/**
 * _strchr - locates a character in a string
 * @s: a string
 * @c: a character
 *
 * Return: pointer to the character in the string, or NULL otherwise
 */
char *_strchr(char *s, char c)
{
	if (s != NULL)
	{
		while (*s != '\0')
		{
			if (*s == c)
				return (s);
			s++;
		}
		/**
		 * If `c` is also '\0',
		 * then return a pointer to the '\0' character in the string
		 */
		if (c == '\0')
			return (s);
	}
	return (NULL);
}

