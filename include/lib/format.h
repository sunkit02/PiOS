#ifndef LIB_PRINT_H
#define LIB_PRINT_H

#include "peripherals/uart.h"
#include <stddef.h>

// Prints numeric value of a character
// Returns pointer to null terminating character of string
char *ascii_str(unsigned char c, char *buf); 

// Converts a signed integer to its string representation
// Returns pointer to null terminating character of string
// Note: buf must of of size 12 or greater
char *int_str(int num, char *buf);

// Converts an integer (signed or unsigned) to its binary representaton as 
// a string.
// Returns pointer to null terminating character of string
// Note: buf must of of size 37 or greater
char *int_bstr(int num, char *buf); 


char *to_bstr(void *ptr, size_t size, char *buf, size_t bufSize);

char *to_bstr_end(void *ptr, size_t size, char *buf, size_t bufSize);

char *to_xstr(void *ptr, size_t size, char *buf, size_t bufSize);

char *to_xstr_end(void *ptr, size_t size, char *buf, size_t bufSize);

#endif // !LIB_PRINT_H
