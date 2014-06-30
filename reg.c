#include <stdio.h>

typedef unsigned int dword;
volatile dword *pwr_cfg;
pwr_cfg = (volatile dword *)0x7E00F804;

void set_pwr_cfg(dword value)
{
  *pwr_cfg = value;
}

void main()
{
  return;
}
