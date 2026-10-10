#include "indicator.h"

void indicator_init(void)
{
    uint8_t i;
    for (i = 0; i < 4; i++)
    {
        config_pin(LED_PORT, i, D_OUTPUT);
        pin_write(LED_PORT, i, D_LOW);
    }
}

void indicator_set_zone(uint8_t zone)
{
    pin_write(LED_PORT, LED_SAFE_PIN,    zone == ZONE_SAFE);
    pin_write(LED_PORT, LED_CAUTION_PIN, zone == ZONE_CAUTION);
    pin_write(LED_PORT, LED_WARNING_PIN, zone == ZONE_WARNING);
    pin_write(LED_PORT, LED_STOP_PIN,    zone == ZONE_STOP);
}