#include <stdio.h>
#include "type_def.h"

#define BIG_ENDIAN 0
#define LITTLE_ENDIAN 1

int TestByteOrder()
{
	short int word = 0x0001;
	char *byte = (char *)&word;

	printf("sizeof(short int) = %d\n", sizeof(short int));
	return (byte[0] ? LITTLE_ENDIAN :  BIG_ENDIAN);
}

bool8 isLittleEndian()
{
  int test_num = 1;
  char *ptr;

  // char pointer
  // MSB - Low address : BIG Endian
  // LSB - Low address : Little Endian
  ptr = (char*)&test_num;
  printf("ptr is %d\n", *ptr);
  
  return *ptr;
}

void show_mem_rep(char *start, int n)
{
	int i;
	for(i=0; i < n; i++)
		printf("[%#x]%.2x\t", &start[i], start[i]);
	printf("\n");
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

  int i = 0x01234567;
  char *ptr = (char *)&i;

  printf("%x\t %x\n", *ptr, *(ptr+1));

  
  show_mem_rep((char *)&i, sizeof(i));

  printf("TestByteOrder = [%d]\n", TestByteOrder());
  
}
