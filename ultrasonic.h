#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#include <stdint.h>
#include "gpio.h"

// Trig = PH4 (Mega pin 7), Echo = PH5 (Mega pin 8)
#define ULTRA_TRIG_PORT  H
#define ULTRA_TRIG_PIN   4
#define ULTRA_ECHO_PORT  H
#define ULTRA_ECHO_PIN   5

#define ULTRA_ERROR          0xFFFF     // returned on timeout (no echo)
#define ULTRA_TIMEOUT_TICKS  60000U     // about 30 ms at 0.5 us per tick

#ifdef __cplusplus
extern "C" {
#endif

void ultra_init(void);
uint16_t ultra_get_distance_cm(void);

#ifdef __cplusplus
}
#endif

#endif