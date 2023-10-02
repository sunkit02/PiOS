#include <stdbool.h>
#include <stdarg.h>

#include "lib/print.h"
#include "peripherals/uart.h"
#include "lib/string.h"
#include "peripherals/uart.h"

// The starting number of the numeric characters in ascii
// Ex: 48 + 0 = '0'
// Ex: 49 + 1 = '1'
// Ex: 50 + 2 = '2'
// Ex: 51 + 3 = '3'
#define ASCII_NUM_BASE 48

// Prints numeric value of a character
// Returns pointer to null terminating character of string
char *ascii_str(unsigned char c, char *buf) {
  int i = 0;
  unsigned char tmp = 0;

  tmp = c / 100;
  if (tmp > 0) {
    buf[i++] = ASCII_NUM_BASE + tmp;
  }
  c %= 100;

  tmp = c / 10;
  if (tmp > 0) {
    buf[i++] = ASCII_NUM_BASE + tmp;
  }
  c %= 10;

  buf[i++] = ASCII_NUM_BASE + c;
  buf[i] = '\0';

  return buf + i;
}

// Converts a signed integer to its string representation
// Returns pointer to null terminating character of string
// Note: buf must of of size 12 or greater
char *int_str(int num, char *buf) {
  // Handle zero
  if (num == 0) {
    buf[0] = '0';
    buf[1] = '\0';

    return buf + 1;
  }

  unsigned int mask = 1 << 31; 
  int i = 0;

  // Check two's complement first bit and converts negative to unsigned
  if (num & mask) {
    num ^= 0xffffffff;
    num += 1;
    // Insert negative sign
    buf[i++] = '-';
  } 

  int currDigit = 0;
  int base = 1000000000;
  // Set flag to true initially to omit leading zeroes
  // Set flag to false once the first non-zero digit is reached
  bool isLeadingZero = true;
  while (base > 0) {
    currDigit = num / base;
    // Append digit to string if non-zero value or is not a leading zero
    if (currDigit > 0 || !isLeadingZero) {
      isLeadingZero = false;
      buf[i++] = ASCII_NUM_BASE + currDigit;
    }
    num %= base;
    base /= 10;
  }

  buf[i] = '\0';

  return buf + i;
}

// Converts an integer (signed or unsigned) to its binary representaton as 
// a string.
// Returns pointer to null terminating character of string
// Note: buf must of of size 37 or greater
char *int_bstr(int num, char *buf) {
  unsigned int mask = 1 << 31;

  int j = 0;
  for (int i = 0; i < 32; i++) {
    if (num & mask) {
      buf[j++] = '1';
    } else {
      buf[j++] = '0';
    }

    mask >>= 1;

    if (i % 4 == 3) {
      buf[j++] = ' ';
    }
  }

  buf[j] = '\0';

  return buf + j;
}


// Can only be string or int
// Use %% to print a %
void printf(char *fmtStr, ...){ 
  char output[10000];
  char *outputPtr = output;
  
  va_list ap;
  va_start(ap, fmtStr);

  // Loop till end of string
  while (*fmtStr != '\0'){
    //check for escape charecter
    if (*fmtStr == '%') {
      fmtStr++;

      switch (*fmtStr) {
        case 'd': {
          int intPassed = va_arg(ap, int);
          int_str(intPassed, outputPtr++);
          break;
        }
        case 's': {
          char *stringPassed = va_arg(ap, char*);
          while (*stringPassed != '\0') {
            *outputPtr++ = *stringPassed++;
          }
          break;
        }
        case '%': {
          *outputPtr++ = '%';
          break;
        }
        default: {
          *outputPtr++ = *fmtStr;
        }
      }
    } else {
      *outputPtr++ = *fmtStr;
    }

    fmtStr++;
  }
  // Add terminating charecter
  *outputPtr = '\0';
  // Clean up weird C variable argument list
  va_end(ap);
  // Print the thing
  uart_puts(output);
}
