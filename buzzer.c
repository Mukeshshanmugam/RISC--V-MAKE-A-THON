#include "buzzer.h"

#define TCCR_3A (*(volatile uint8_t*)0x90)
#define TCCR_3B (*(volatile uint8_t*)0x91)
#define TCNT_3  (*(volatile uint16_t*)0x94)
#define ICR_3   (*(volatile uint16_t*)0x96)
#define OCR_3A  (*(volatile uint16_t*)0x98)

void buzzer_init(void)
{
    config_pin(BUZZER_PORT, BUZZER_PIN, D_OUTPUT);
    pin_write(BUZZER_PORT, BUZZER_PIN, D_LOW);

    TCCR_3A = (1 << 1);                          // WGM31
    TCCR_3B = (1 << 4) | (1 << 3) | (1 << 1);    // WGM33, WGM32 (fast PWM, TOP = ICR3), prescaler 8
}

void buzzer_on(uint16_t freq_hz)
{
    uint16_t top;

    if (freq_hz < 40) freq_hz = 40;              // keeps TOP inside 16 bits

    top = (uint16_t)(2000000UL / freq_hz) - 1;
    TCNT_3 = 0;
    ICR_3  = top;
    OCR_3A = top / 2;                            // 50 % duty
    TCCR_3A |= (1 << 7);                         // COM3A1: connect OC3A to the pin
}

void buzzer_off(void)
{
    TCCR_3A &= (uint8_t)~(1 << 7);               // disconnect OC3A
    pin_write(BUZZER_PORT, BUZZER_PIN, D_LOW);
}