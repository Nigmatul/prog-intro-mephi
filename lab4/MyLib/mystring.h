#ifndef __mystring_h
#define __mystring_h

#include <stdlib.h>
#include <stdio.h>

#define BUFSIZE 100

char *readline(const char* prompt);
char *strcpy(char *dest, const char *src);
char *strtok(char *str, const char *delim);
size_t strlen(const char *str); 
char *strdup(const char *str);
char *strcat(char *dest, const char *src);
size_t strcspn(const char *str, const char *reject);
size_t strspn(const char *str, const char *accept);

#endif // __mystring_h
