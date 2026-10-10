#ifndef SEG7_H
#define sEG7_H
#include"gpio.h"
// display numbers from 0 to 9
 extern const uint8_t a[];
// function to display the single digit 
void single_d(uint8_t port_name, uint8_t value);
// function to display the two digit 
void double_d (uint8_t port_name,uint8_t selection_port,uint8_t value);

#endif