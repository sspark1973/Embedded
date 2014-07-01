#include <stdio.h>
#include <stddef.h>
//#include "type_def.h"

#define DEBUG_PORT ((unsigned char*)(0x7E00F804))

//typedef unsigned long dword;
//unsigned char *pwr_cfg = (unsigned char *)DEBUG_PORT;
unsigned char *pwr_cfg;
(unsigned char *)pwr_cfg = (unsigned char *)DEBUG_PORT;

/* C99 adds support for flexible array members to structures. 
This form of array declaration is allowed as the last element in structures only, 
and differs from normal arrays in that no length is specified to the compiler. 
For a structure named s containing a flexible array member named a, 
sizeof s is therefore equivalent to offsetof(s, a):

Thus, in this case the sizeof operator returns the size of the structure, 
including any padding, 
but without any storage allowed for the array. 
In the above example, the following output will be produced on most platforms:
sizeof (struct flexarray) = 4
*/
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
