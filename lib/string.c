/////////////////////////////////////////////////
////   String Functions necesary for Lib C   ////
////////////////////////////////////////////////
//memcpy memcat memset strcmp strtok


#include "string.h"

size_t strlen(char *str) {
  size_t i = 0;
  while (str[i]) {
    i++;  
  }
  return i;
}

char* strcat(char* destination, const char* source){
  char* originalDestination = destination;
  while(*destination != '\0'){
    destination++;
  }
  while (*source != '\0') {
    *destination = *source;
    destination++;
    source++;
  }
  *destination = '0';
  return originalDestination;
}

void *memcpy(void *dest, const void *src, size_t n){
  
  int i = 0; 
  
  while(i < n){
    *(char *)dest = *(char *)src;
    dest++;
    src++;
    i++;
  }

  return dest;
}

void *memcat(void *dest, const void *src1, const void *src2, size_t src1N, size_t src2N) {
  int i = 0;
  while(i < src1N){
    *(char *)dest = *(char *)src1;
    dest++;
    src1++;
    i++;
    }
   while(i < src1N + src2N){
    *(char *)dest = *(char *)src2;
    dest++;
    src2++;
    i++;
    }

  return dest;
}
  
void *memset(void *src, int c, size_t n) {
  int i = 0;
  while (i < n){
    *(char *)src = c;
    src++;
    i++;
  }

  return src;
}

int strcmp(const char *str1, const char *str2) {
  while (*str1 != '\0' && *str2 != '\0'){
    if (*str1 != *str2){
      return 0;
    }
    str1++;
    str2++;
  }
  return 1;
}
