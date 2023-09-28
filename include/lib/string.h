/////////////////////////////////////////////////
////   String Functions necesary for Lib C   ////
/////////////////////////////////////////////////

#ifndef LIB_STRING_H
#define LIB_STRING_H

typedef unsigned int size_t;


size_t strlen(char *str);
char* strcat(char* destination, const char* source);
void *memcpy(void *dest, const void *src, size_t n);
void *memcat(void *dest, const void *src1, const void *src2, size_t src1N, size_t src2N);
void *memset(void *str, int c, size_t n);
int strcmp(const char *str1, const char *str2);

#endif // !LIB_STRING_H
