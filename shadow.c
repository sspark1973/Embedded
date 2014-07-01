typedef struct
{
  int32 flag:3;
      data_1:20;
      data_2:9;
} REGISTER_SHADOW;

int main(int argc, char **argv)
{
  int32 reg_data;
  REGISTER_SHADOW R_0;
  
  R_0.flag = 2;
  R_0.data_1 = 16;
  R_0.data_2 = 22;
  
  if(reg_data & 0x20) // binary 100000 - mask
  if(reg_data >> 6 & 0x1) // if(reg_data & (1<<6))
  if(reg_data >> 6 & 0x3) // 2 bits
  
  reg_data = reg_data | 0x8; // set
  reg_data = reg_data | (0x1 << 3);
  reg_data |= (0x1 << 3);
  
  reg_data &= ~(1 << 3); // clear
  
  reg_data ^= (1 << 3); // XOR same->0 differ->1
  
  return 0;
}