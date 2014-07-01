#include <stdio.h>

typedef long unsigned int dword;

/*
MCU의 clock을 configuration할 수 있는 주소와 값들을 Macro로 정했다고 해보죠. 
MCU의 Data Sheet를 보았더니 그 주소가 0xC000CB00이고요, 32bit register이고요, 
그 중에 LSB bit 2,3이 MCU의 Data 이고요. Read, Write가 모두 가능한 Register이고요, 
LSB 2,3bit가 
0x0인 경우에는 Clock을 disable 하는 거고, 
0x1인 경우에는 Clock을 enable 하는 거고, 
0x2인 경우에는 enable된 Clock의 주기를 반으로 줄이는 거고, 
0x3인 경우에는 enable된 Clock의 주기를 두 배로 올리는 거라면요!
*/
#define HWCIO_MCU_CLK_ADDR 0xC000CB00
#define HWCIO_MCU_CLK_MSK 0x3
#define HWCIO_MCU_CLK_SHIFT 0x2
#define HWCIO_MCU_CLK_DIS_VALUE 0x0
#define HWCIO_MCU_CLK_EN_VALUE 0x0
#define HWCIO_MCU_CLK_TWICE_VALUE 0x3
#define HWCIO_MCU_CLK_HALF_VALUE 0x2


#define IO_OUT(target, val) \
(*((volatile dword *)(HWCIO_##target##_ADDR))) = \
((dword)(HWCIO_##target##_##val##_VALUE & HWCIO_##target##_MSK) << HWCIO_##target##_SHIFT)

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
  
  /* Clock을 살리고 2배로 뻥튀기 시키고 싶을 때, */
  IO_OUT(MCU_CLK, TWICE);
  
  printf("%d\n", (*((volatile dword *)(HWCIO_MCU_CLK_ADDR))));
  
  return 0;
}

/*
if (x>10)
do { 
scanf ("%d", &x); 
printf ("\n%d", x); 
} while (0);
else
system_exit() ;

괄호만 넣으면 되지 않느냐 하는 의문이 생기시겠지만 만약 괄호만 넣어주고서 한번 해볼까요?

#define READ_PRINT_VALUE(x)
{ \
scanf ("%d", &x); \
printf ("\n%d", x); \
} 

요렇게 해주면, 어떻게 해석되느냐

if (x>10)
{ 
scanf ("%d", &x); 
printf ("\n%d", x); 
} ;
else
system_exit() ;

else 앞에 왠 의미 없는 ;가 하나 들어 갔죠.
*/

