#include <stdio.h>
//#include "type_def.h"

#define DEBUG_PORT ((unsigned char*)(0x7E00F804))

//typedef unsigned long dword;
unsigned char *pwr_cfg = (unsigned char *)DEBUG_PORT;
//pwr_cfg = (unsigned char *)DEBUG_PORT;

void set_pwr_cfg(unsigned char value)
{
  *pwr_cfg = value;
}

void main()
{
  printf("%zu\n", sizeof(unsigned char));
  printf("%zu\n", sizeof(int));
  return;
}
