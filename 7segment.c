#include"7segment.h"
   const uint8_t a[10]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
// function to display single digit.
void single_d(uint8_t port_name, uint8_t value)
{
    *DAT[port_name]=a[value];
}
// display double digit .
void double_d(uint8_t port_name,uint8_t selection_port,uint8_t value)
{
  volatile long b = 0;
	*DAT[selection_port] = 0xFF;
	while(b<100000)
	{
		*DAT[port_name] = a[value%10];
		*DAT[selection_port] = ~0x02;
		*DAT[selection_port] = 0x03;
		*DAT[port_name] = a[value/10];
		*DAT[selection_port] = ~0x01;
		*DAT[selection_port] = 0x03;
		b++;
	}
}