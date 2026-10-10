#include"gpio.h"


volatile uint8_t *DDR[] = { (volatile uint8_t*)0x21,(volatile uint8_t*)0x24,(volatile uint8_t*)0x27,(volatile uint8_t*)0x2A,
                            (volatile uint8_t *)0x2D,(volatile uint8_t *)0x30,(volatile uint8_t *)0x33,(volatile uint8_t *)0x101,
                            (volatile uint8_t *)0x104,(volatile uint8_t *)0x107,(volatile uint8_t *)0x10A};

volatile uint8_t *DAT[] = {(volatile uint8_t *)0x22,(volatile uint8_t *)0x25,(volatile uint8_t *)0x28,(volatile uint8_t *)0x2B,
                            (volatile uint8_t *)0x2E,(volatile uint8_t *)0x31,(volatile uint8_t *)0x34,(volatile uint8_t *)0x102,
                            (volatile uint8_t *)0x105,(volatile uint8_t *)0x108,(volatile uint8_t *)0x10B};

volatile uint8_t *RD[]  = {(volatile uint8_t *)0x20,(volatile uint8_t *)0x23,(volatile uint8_t *)0x26,(volatile uint8_t *)0x29,
                           (volatile uint8_t *)0x2C,(volatile uint8_t *)0x2F,(volatile uint8_t *)0x32,(volatile uint8_t *)0x100,
                           (volatile uint8_t *)0x103,(volatile uint8_t *)0x106,(volatile uint8_t *)0x109};


// set direction for entire port.
void config_reg (uint8_t port_name,uint8_t direction) //config_reg(port_name,output/input) direction:output/input
{
    *DDR[port_name]=direction;
}
 // set the direction for a particular pin.
void config_pin (uint8_t port_name, uint8_t pin,uint8_t direction) //config_pin(port_name,pin,direction)
{
    if(direction==1U)
    {
        *DDR[port_name]|=(1<<pin); //set the pin as output.
    }
    else
    {
        *DDR[port_name]&=~(1<<pin); // set the pin as input.
    }
}
 //set data for entire port
 void reg_write (uint8_t port_name , uint8_t status) //reg_write(port_name , status) status: HIGH/LOW
 {
    *DAT[port_name]=status;
 }
 //set data for a particular for a pin.
 void pin_write (uint8_t port_name,uint8_t pin,uint8_t status) 
 {
    if(status==1U)
    {
        *DAT[port_name]|=(1<<pin);
    }
    else
    {
        *DAT[port_name]&=~(1<<pin);
    }
 }
 // read register
 uint8_t reg_read (uint8_t port_name) // read and return value from the port
 {
         return*RD[port_name];
 }

 // read a particular pin  (NEW)
 uint8_t pin_read (uint8_t port_name, uint8_t pin)
 {
     return (*RD[port_name] >> pin) & 1U;
 }

 //Additional functions 
 
//turn on the LED on
void led_on(uint8_t port_name, uint8_t pin)
{
    *DAT[port_name]|=(1<<pin);
}

void delay_time (uint8_t x)
{
    for(volatile unsigned long i=0; i<10000UL*x; i++);
}


// blinking led 
void led_blink (uint8_t port_name,uint8_t pin)
{
    *DAT[port_name]|=(1<<pin);
    delay_time(1);       
    *DAT[port_name]&=~(1<<pin);
    delay_time(1);
                                       
}


//led chaser 
void led_chaser (uint8_t port_name)
{
    while(1)
    {
        for(volatile int i=0; i<8;i++)
        {
            *DAT[port_name]=(1U<<i);
            delay_time(1);                            // delay
        }
    }
}