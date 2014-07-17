#include <stdio.h>
#include "type_def.h"

bool8 isLittleEndian()
{
  int test_num = 1;
  char *ptr;
  
  ptr = (char*)&test_num;
  printf("ptr is %d\n", *ptr);
  
  return *ptr;
}


main()
{
  unsigned int n = 1;
  char *p;
  
  p = (char *)&n;
  
  if(*p == 1)
    printf("Little Endian\n");
  else if(*(p + sizeof(int) - 1) == 1)
    printf("Big Endian\n");
  else
    printf("????\n");
    
  isLittleEndian();
}
