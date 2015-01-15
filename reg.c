#include <stdio.h>
#include <stddef.h>
//#include "type_def.h"

typedef unsigned int dword;
//volatile dword *pwr_cfg;
//pwr_cfg = (volatile dword *)0x7E00F804;

#define DEBUG_PORT ((dword*)(0x7E00F804))

volatile dword *pwr_cfg = (volatile dword *)DEBUG_PORT;
//unsigned char *pwr_cfg;
//pwr_cfg = DEBUG_PORT;

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
  char val2;
  //int array[];
  int *array;
};

struct bitarray {
	unsigned int a:1;
	unsigned int b:1;
	unsigned int c:1;

};

void set_pwr_cfg(unsigned int value)
{
  *pwr_cfg = value;
}

int main(int argc, char **argv)
{
  printf("%d\n", sizeof(unsigned char));
  printf("%d\n", sizeof(int));
  printf("pwr_cfg [%#010x]\n", pwr_cfg);
  
  printf("offsetof (flexarray, val) = %d\n", offsetof(struct flexarray, val));
  printf("offsetof (flexarray, val2) = %d\n", offsetof(struct flexarray, val2));
  printf("offsetof (flexarray, array) = %d\n", offsetof(struct flexarray, array));
  printf("sizeof (struct flexarray) = %d\n", sizeof(struct flexarray));

  printf("sizeof (struct bitarray) = %d\n", sizeof(struct bitarray));

  char c = 'A';

  printf("A = %#04x\n", c);
  
  return 0;
}
