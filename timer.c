#include <stdint.h>
#include <avr/io.h>
#include "timer.h"

#define TCCR_1A *(volatile uint8_t*)0x80
#define TCCR_1B *(volatile uint8_t*)0x81
#define OCR_1A  *(volatile uint16_t*)0x88     // 16-bit
#define TIFR_1  *(volatile uint8_t*)0x36
#define TCNT_1  *(volatile uint16_t*)0x84     // 16-bit (low byte at 0x84)

// ---------- millisecond delay (unchanged idea, bugs fixed) ----------
void Delay_Millsec(volatile unsigned int MS)
{
    TCCR_1A = 0x00;
    TCCR_1B = 0x00;

    TCCR_1B |= (1 << 3);                 // WGM12: CTC mode
    TCCR_1B |= (1 << 2) | (1 << 0);      // prescaler 1024

    while (MS--)
    {
        TCNT_1 = 0;
        OCR_1A = 15;                     // about 1 ms

        while (!(TIFR_1 & (1 << OCF1A))) { }

        TIFR_1 = (1 << OCF1A);           // clear flag
    }

    TCCR_1B = 0;                         // stop timer
}

// ---------- microsecond timing ----------
void Timer1_Start_us(void)
{
    TCCR_1A = 0x00;                      // normal mode
    TCCR_1B = (1 << 1);                  // CS11: prescaler 8, 1 tick = 0.5 us
}

void Timer1_Reset(void)
{
    TCNT_1 = 0;
}

uint16_t Timer1_Read(void)
{
    return TCNT_1;
}

void Delay_Microsec(uint16_t us)
{
    if (us > 32000) us = 32000;          // avoid 16-bit overflow of us*2
    TCNT_1 = 0;
    while (TCNT_1 < (uint16_t)(us * 2)) { }
}