#include "lib.h"

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

/**
 * _strcpy - copies the string src to dest, including the null character.
 * @src: source string
 * @dest: destination string
 *
 * Return: void
 */
char *_strcpy(char *dest, char *src)
{
	int i = 0;

	if (dest != NULL && src != NULL)
	{
		while (*src != '\0')
			dest[i++] = *(src++);
		dest[i] = '\0';
	}
	return (dest);
}

/**
 * _strstr - finds the first occurrence of the substring needle
 * in the string haystack
 * @haystack: a string
 * @needle: a substring
 *
 * Return: pointer to the first occurrence of the substring, NULL otherwise
 */
char *_strstr(char *haystack, char *needle)
{
	char *h = haystack, *n = needle;

	if (haystack != NULL && needle != NULL)
	{
		/* If `needle` is empty, return haystack */
		if (*needle == '\0')
			return (haystack);
		/* Now search for `needle`, in the `haystack` */
		while (*haystack != '\0')
		{
			while (*h != '\0' && *n != '\0')
				if (*(h++) != *(n++))
					break;
			/* If `n` is exhausted then `needle` is a match */
			if (*n == '\0')
				return (haystack);
			/* If `needle` is not a match, move along */
			h = ++haystack;
			/* Move `n` back to the beginning of `needle` */
			n = needle;
		}
	}
	return (NULL);
}

