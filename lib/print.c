#include "lib/print.h"

// Prints numeric value of a character
// Returns pointer to null terminating character of string
char *ascii_str(unsigned char c, char *buf) {
  static const char ASCII_NUM_BASE = 48;
  
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


// Prints binary string of an unsigned integer
// Returns pointer to null terminating character of string
// Note: buf must of of size 37 or greater
char *uint_bstr(unsigned int num, char *buf) {
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
