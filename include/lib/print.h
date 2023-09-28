#ifndef LIB_PRINT_H
#define LIB_PRINT_H

#include "peripherals/uart.h"

// Prints numeric value of a character
// Returns pointer to null terminating character of string
char *ascii_str(unsigned char c, char *buf); 

// Prints binary string of an unsigned integer
// Returns pointer to null terminating character of string
// Note: buf must of of size 37 or greater
char *uint_bstr(unsigned int num, char *buf); 

#endif // !LIB_PRINT_H
