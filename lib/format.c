#include <stdbool.h>
#include <stddef.h>

#include "lib/format.h"
#include "peripherals/uart.h"

/**
* The starting number of the numeric characters in ascii
*
* Ex: 48 + 0 = '0'
* Ex: 49 + 1 = '1'
* Ex: 50 + 2 = '2'
* Ex: 51 + 3 = '3'
*/
#define ASCII_NUM_BASE 48

// The number of bits in a byte
#define BYTE_SIZE 8

// 0 - Little endian
// 1 - Big endian
#define ENDIANNESS 0

static const char HEX_CHARS[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

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

  // Overwrite trailing space with '\0'
  if (buf[j - 1] == ' ') {
    j--;
  }

  buf[j] = '\0';

  return buf + j;
}

// Generic binary dump
char *to_bstr(void *ptr, size_t size, char *buf, size_t bufSize) {
  unsigned char *input = ptr;

  // Mask for each byte
  unsigned char mask = 1 << 7; 

  size_t charsWritten = 0;

  for (int i = 0; i < size; i++) {
    mask = 1 << 7;

    for (int j = 0; j < BYTE_SIZE; j++) {
      if (charsWritten + 1 >= bufSize) break;

      if ((input[i] & mask) > 0) {
        buf[charsWritten++] = '1';
      } else {
        buf[charsWritten++] = '0';
      }
      mask >>= 1;
      if (j % 4 == 3) {
        buf[charsWritten++] = ' ';
      }
    }
  }

  // Overwrite trailing space with '\0'
  if (buf[charsWritten - 1] == ' ') {
    charsWritten--;
  }

  buf[charsWritten] = '\0';

  return buf + charsWritten;

}


// Generic binary string dump endian aware
char *to_bstr_end(void *ptr, size_t size, char *buf, size_t bufSize) {
  unsigned char *input = ptr;

  // Mask for each byte
  unsigned char mask = 1 << 7; 

  size_t charsWritten = 0;

#if ENDIANNESS == 0
  for (int i = size - 1; i >= 0; i--)
#else
  for (int i = 0; i < n; i++)
#endif
  {
    mask = 1 << 7;

    for (int j = 0; j < BYTE_SIZE; j++) {
      if (charsWritten + 1 >= bufSize) break;

      if ((input[i] & mask) > 0) {
        buf[charsWritten++] = '1';
      } else {
        buf[charsWritten++] = '0';
      }
      mask >>= 1;
      if (j % 4 == 3) {
        buf[charsWritten++] = ' ';
      }
    }
  }

  // Overwrite trailing space with '\0'
  if (buf[charsWritten - 1] == ' ') {
    charsWritten--;
  }

  buf[charsWritten] = '\0';

  return buf + charsWritten;
}

// Generic hex dump
char *to_xstr(void *ptr, size_t size, char *buf, size_t bufSize) {
  unsigned char *input = ptr;

  unsigned char upperByte = 0;
  unsigned char lowerByte = 0;

  size_t charsWritten = 0;
  for (size_t i = 0; i < size; i++) {
    if (charsWritten + 1 >= bufSize) break;

    // Acquire the upper and lower half of each byte
    upperByte = (input[i] & 0xf0) >> 4;
    lowerByte = input[i] & 0x0f;

    buf[charsWritten++] = HEX_CHARS[upperByte];
    buf[charsWritten++] = HEX_CHARS[lowerByte];
    buf[charsWritten++] = ' ';
  }

  // Overwrite trailing space with '\0'
  if (buf[charsWritten - 1] == ' ') {
    charsWritten--;
  }

  buf[charsWritten] = '\0';

  return buf + charsWritten;
}


// Endian aware hex dump (doesn't work well with nested arrays)
char *to_xstr_end(void *ptr, size_t size, char *buf, size_t bufSize) {
  unsigned char *input = ptr;

  unsigned char upperByte = 0;
  unsigned char lowerByte = 0;

  size_t charsWritten = 0;

#if ENDIANNESS == 0
  for (int i = size - 1; i >= 0; i--)
#else
  for (int i = 0; i < size; i++)
#endif
  {
    if (charsWritten + 1 >= bufSize) break;

    // Acquire the upper and lower half of each byte
    upperByte = (input[i] & 0xf0) >> 4;
    lowerByte = input[i] & 0x0f;

    buf[charsWritten++] = HEX_CHARS[upperByte];
    buf[charsWritten++] = HEX_CHARS[lowerByte];
    buf[charsWritten++] = ' ';
  }

  // Overwrite trailing space with '\0'
  if (buf[charsWritten - 1] == ' ') {
    charsWritten--;
  }

  buf[charsWritten] = '\0';

  return buf + charsWritten;
}
