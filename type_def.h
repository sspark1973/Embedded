#ifndef TYPE_DEF_H
#define TYPE_DEF_H

#include <stdint.h>

typedef uint8_t   bool8;
typedef uint8_t   byte;
typedef uint16_t  word;
typedef uint32_t  dword;
typedef uint8_t   uint8;
typedef uint16_t  uint16;
typedef uint32_t  uint32;
typedef int8_t    int8;
typedef int16_t   int16;
typedef int32_t   int32;

#undef NULL
#define NULL 0

#define OK     1
#define FAIL   0
#define YES    1
#define NO     0
#define TRUE   1
#define FALSE  0

#endif
