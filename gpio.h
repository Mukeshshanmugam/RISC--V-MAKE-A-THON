#ifndef GPIO_H
#define GPIO_H
#include <stdint.h>

#define D_HIGH 1U
#define D_LOW 0U

#define D_OUTPUT 1U
#define D_INPUT 0U

#define OUT 0XFF
#define IN 0X00

// port names (index into the DDR, DAT and RD arrays)
#define A 0
#define B 1
#define C 2
#define D 3
#define E 4
#define F 5
#define G 6
#define H 7
#define J 8
#define K 9
#define L 10

#ifdef __cplusplus
extern "C" {
#endif

extern volatile uint8_t *DDR[];
extern volatile uint8_t *DAT[];
extern volatile uint8_t *RD[];

void config_reg(uint8_t port_name, uint8_t direction);
void config_pin(uint8_t port_name, uint8_t pin, uint8_t direction);
void reg_write(uint8_t port_name, uint8_t status);
void pin_write(uint8_t port_name, uint8_t pin, uint8_t status);
uint8_t reg_read(uint8_t port_name);
uint8_t pin_read(uint8_t port_name, uint8_t pin);
void delay_time(uint8_t x);
void led_on(uint8_t port_name, uint8_t pin);
void led_blink(uint8_t port_name, uint8_t pin);
void led_chaser(uint8_t port_name);

#ifdef __cplusplus
}
#endif

#endif