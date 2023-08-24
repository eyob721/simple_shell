#ifndef LIBS_H
#define LIBS_H

/* ------------------------------------------------------------------------- */
/*                         LIB - HEADERS AND CONSTANTS                       */
/* ------------------------------------------------------------------------- */
/* STANDARD HEADERS */
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <linux/limits.h>

/* CUSTOM PRINTF HEADER */
#include "printf.h"

/* ------------------------------------------------------------------------- */
/*                              STDIO LIBRARY                                */
/* ------------------------------------------------------------------------- */

int _putchar(char c);
int _printf(const char *format, ...);
int _dprintf(int fd, const char *format, ...);
int _vdprintf(int fd, const char *format, va_list args);

/* ------------------------------------------------------------------------- */
/*                             STRING LIBRARY                                */
/* ------------------------------------------------------------------------- */

/* 1 */
char *_memset(char *s, char b, unsigned int n);
char *_memcpy(char *dest, char *src, unsigned int n);
int _strlen(char *s);
int _strcmp(char *s1, char *s2);
int _strncmp(char *s1, char *s2, int n);

/* 2 */
char *_strcat(char *dest, char *src);
char *_strdup(char *str);
unsigned int _strspn(char *s, char *accept);
char *_strpbrk(char *s, char *accept);
char *_strtok_r(char *str, char *delim, char **save_ptr);

/* 3 */
char *_strchr(char *s, char c);
char *_strcpy(char *dest, char *src);
char *_strstr(char *haystack, char *needle);

/* ------------------------------------------------------------------------- */
/*                             STDLIB LIBRARY                                */
/* ------------------------------------------------------------------------- */

int _abs(int x);
int _atoi(char *s);
char *_itoa(int n);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);

/* ------------------------------------------------------------------------- */
/*                              CTYPE LIBRARY                                */
/* ------------------------------------------------------------------------- */

int _isdigit(int c);

/* ------------------------------------------------------------------------- */
#endif
