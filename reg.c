#include <stdio.h>

#define DEBUG_PORT ((unsigned char*)(0x7E00F804))

//typedef unsigned long dword;
volatile unsigned char *pwr_cfg;
pwr_cfg = (volatile unsigned char *)DEBUG_PORT;

void set_pwr_cfg(unsigned char value)
{
  *pwr_cfg = value;
}

void main()
{
  return;
}
