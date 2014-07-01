#include <stdio.h>


/*
#define READ_PRINT_VALUE(x) \
scanf("%d", &x); \
printf("\n%d",x);

do~while(0)는 진짜 여러 번 반복되는 구문을 간단하게 줄이려고 쓰인다고 보면 됩니다. 
왜냐하면, do~while(0)을 씀으로써 가능해지는 것이 있어서 그런데요. 
일단 {}로 묶여 있으니까, 그 안에서 local variable을 선언해서 사용할 수가 있습니다. 
두 번째로는 불확실한 if문의 사용을 확실하게 해줍니다. 예를 들어볼까요? 

if (x>10)
READ_PRINT_VALUE(x);

if (x>10)
scanf ("%d", &x); 
printf ("\n%d", x); 

if (x>10)
READ_PRINT_VALUE(x)
else
system_exit();

if (x>10)
scanf ("%d", &x); 
printf ("\n%d", x); ;
else
system_exit() ;

Compiler가 에라!
*/


#define READ_PRINT_VALUE(x) \
do { \
  scanf("%d", &x); \
  printf("\n%d",x); \
} while(0)

int main(int argc, char **argv)
{
  int value;
  
  READ_PRINT_VALUE(value);
  
  return 0;
}
