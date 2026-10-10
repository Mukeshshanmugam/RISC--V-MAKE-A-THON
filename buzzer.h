#ifndef BUZZER_H
#define BUZZER_H

#include <stdint.h>
#include "gpio.h"

#define BUZZER_PORT  E
#define BUZZER_PIN   3              // PE3 = OC3A = Mega pin 5

#ifdef __cplusplus
extern "C" {
#endif

void buzzer_init(void);
void buzzer_on(uint16_t freq_hz);   // start a tone at freq_hz
void buzzer_off(void);              // stop the tone

#ifdef __cplusplus
}
#endif

#endif