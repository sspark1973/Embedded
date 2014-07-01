#include <stdio.h>
//#include "type_def.h"

#define DEBUG_PORT ((unsigned char*)(0x7E00F804))

//typedef unsigned long dword;
unsigned char *pwr_cfg = (unsigned char *)DEBUG_PORT;
//pwr_cfg = (unsigned char *)DEBUG_PORT;

struct flexarray
{
  char val;
  int array[];
};

void set_pwr_cfg(unsigned char value)
{
  *pwr_cfg = value;
}

int main(int argc, char **argv)
{
  printf("%d\n", sizeof(unsigned char));
  printf("%d\n", sizeof(int));
  
  printf("offsetof (flexarray, val) = %d\n", offsetof(struct flexarray, val));
  printf("offsetof (flexarray, array) = %d\n", offsetof(struct flexarray, array));
  printf("sizeof (struct flexarray) = %d\n", sizeof(struct flexarray));
  
  return 0;
}
