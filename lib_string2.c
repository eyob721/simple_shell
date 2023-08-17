#include "lib.h"

/**
 * _strcat - concatenates two strings
 * @dest: destination string
 * @src: source string
 *
 * Return: destination string
 */
char *_strcat(char *dest, char *src)
{
	char *d = dest;

	if (dest != NULL && src != NULL)
	{
		while (*d != '\0')
			d++;
		while (*src != '\0')
			*(d++) = *(src++);
		*d = '\0';
	}
	return (dest);
}

/**
 * _strdup - a function that returns a pointer to a newly allocated space in
 *			 memory, which contains a copy of the string given as a parameter
 * @str: a given string
 *
 * Return: pointer to a newly allocated duplicate of the given string, or
 *		   NULL, if the given string is NULL, or if memory allocation failed
 */
char *_strdup(char *str)
{
	int i;
	char *dup;

	if (str == NULL)
		return (NULL);
	/* Find length for str, use i to store length */
	for (i = 0; str[i] != '\0'; i++)
		;
	dup = malloc(sizeof(char) * (i + 1)); /* +1 for '\0' character*/
	if (dup == NULL)
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
		dup[i] = str[i];
	dup[i] = '\0';
	return (dup);
}

/**
 * _strspn - returns the number of bytes in the initial segment of s which
 * consist only of bytes from accept
 * @s: a string
 * @accept: a prefix substring
 *
 * Return: number of bytes
 */
unsigned int _strspn(char *s, char *accept)
{
	unsigned int count = 0;
	char *a = accept;

	if (s != NULL && accept != NULL)
	{
		while (*s != '\0' && *s != ' ')
		{
			/* Check if a character from the string `s` is in `accept` */
			while (*a != '\0')
			{
				if (*s == *(a++))
				{
					count++;
					break;
				}
			}
			/* Move to the next character in `s` */
			s++;
			/* Move back `a` to the begnning of `accept` */
			a = accept;
		}
	}
	return (count);
}

/**
 * _strpbrk - locates the first occurrence in the string s of
 *			  any of the bytes in accept.
 * @s: a string
 * @accept: search key string
 *
 * Return: pointer to the found character in the string s, NULL otherwise
 */
char *_strpbrk(char *s, char *accept)
{
	char *a = accept;

	if (s != NULL && accept != NULL)
	{
		/* Check if a character from the string `s` is in `accept` */
		while (*s != '\0')
		{
			while (*a != '\0')
				if (*s == *(a++))
					return (s);
			/* Move to the next character in `s` */
			s++;
			/* Move `a` back to the begnning of `accept` */
			a = accept;
		}
	}
	return (NULL);
}

/**
 * _strtok_r - a function that breaks a string into a sequence of zero or
 *			   more nonempty tokens.
 * @str: string to be broken down
 * @delim: delimiter charaters to look for in the string
 * @save_ptr: a double pointer to save the start of the next token
 *
 * Return: a pointer to a null-terminated string containing the current token
 *		   or NULL if there are no more tokens in the string
 */
char *_strtok_r(char *str, char *delim, char **save_ptr)
{
	char *start = NULL;

	if (delim == NULL || save_ptr == NULL || (str == NULL && *save_ptr == NULL))
		return (NULL);
	/* Determine starting point */
	if (str != NULL)
		start = str;
	else
		start = *save_ptr;
	/* Skip all delimiter charater, find the current token */
	while (*start != '\0' && _strchr(delim, *start) != NULL)
		++start;
	/* If there are no more tokens, return NULL */
	if (*start == '\0')
		return (NULL);
	/* Find the next token starting point */
	*save_ptr = _strpbrk(start, delim);
	/* null-terminate the current token */
	if (*save_ptr != NULL)
	{
		**save_ptr = '\0';
		++(*save_ptr);
	}
	return (start);
}
