


#ifndef timer_h
#define timer_h

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void Delay_Millsec(volatile unsigned int MS);   // 1 ms steps (CTC, prescaler 1024)

void Timer1_Start_us(void);                     // free-running, 0.5 us per tick
void Timer1_Reset(void);                        // TCNT1 = 0
uint16_t Timer1_Read(void);                     // read TCNT1 (ticks)
void Delay_Microsec(uint16_t us);               // delay in microseconds

#ifdef __cplusplus
}
#endif

#endif