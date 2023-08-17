#ifndef LIBS_H
#define LIBS_H

#include <stdlib.h>

/* Custom headers */
#include "printf.h"

/* <string> library 1 */
char *_memset(char *s, char b, unsigned int n);
char *_memcpy(char *dest, char *src, unsigned int n);
int _strlen(char *s);
int _strcmp(char *s1, char *s2);
char *_strchr(char *s, char c);

/* <string> library 2 */
char *_strcat(char *dest, char *src);
char *_strdup(char *str);
unsigned int _strspn(char *s, char *accept);
char *_strpbrk(char *s, char *accept);
char *_strtok_r(char *str, char *delim, char **save_ptr);

/* <stdlib> library */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
int _abs(int x);

/* <ctype> library */
int _isdigit(int c);

#endif
