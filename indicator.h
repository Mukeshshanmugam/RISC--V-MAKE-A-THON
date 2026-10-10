#ifndef INDICATOR_H
#define INDICATOR_H

#include <stdint.h>
#include "gpio.h"

#define LED_PORT         L
#define LED_SAFE_PIN     0          // pin 49
#define LED_CAUTION_PIN  1          // pin 48
#define LED_WARNING_PIN  2          // pin 47
#define LED_STOP_PIN     3          // pin 46

#define ZONE_NONE        0
#define ZONE_SAFE        1
#define ZONE_CAUTION     2
#define ZONE_WARNING     3
#define ZONE_STOP        4

#ifdef __cplusplus
extern "C" {
#endif

void indicator_init(void);
void indicator_set_zone(uint8_t zone);     // lights only that zone's LED (ZONE_NONE = all off)

#ifdef __cplusplus
}
#endif

#endif