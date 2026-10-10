#include "ultrasonic.h"
#include "timer.h"

void ultra_init(void)
{
    config_pin(ULTRA_TRIG_PORT, ULTRA_TRIG_PIN, D_OUTPUT);
    config_pin(ULTRA_ECHO_PORT, ULTRA_ECHO_PIN, D_INPUT);
    pin_write(ULTRA_TRIG_PORT, ULTRA_TRIG_PIN, D_LOW);
}

uint16_t ultra_get_distance_cm(void)
{
    uint16_t ticks;

    Timer1_Start_us();                          // set up the timer for this measurement

    // 10 us trigger pulse
    pin_write(ULTRA_TRIG_PORT, ULTRA_TRIG_PIN, D_LOW);
    Delay_Microsec(2);
    pin_write(ULTRA_TRIG_PORT, ULTRA_TRIG_PIN, D_HIGH);
    Delay_Microsec(10);
    pin_write(ULTRA_TRIG_PORT, ULTRA_TRIG_PIN, D_LOW);

    // wait for Echo to go HIGH
    Timer1_Reset();
    while (pin_read(ULTRA_ECHO_PORT, ULTRA_ECHO_PIN) == 0)
    {
        if (Timer1_Read() > ULTRA_TIMEOUT_TICKS) return ULTRA_ERROR;
    }

    // measure how long Echo stays HIGH
    Timer1_Reset();
    while (pin_read(ULTRA_ECHO_PORT, ULTRA_ECHO_PIN) == 1)
    {
        if (Timer1_Read() > ULTRA_TIMEOUT_TICKS) return ULTRA_ERROR;
    }
    ticks = Timer1_Read();

    // 1 tick = 0.5 us, 58 us per cm  ->  cm = ticks / 116 (rounded)
    return (ticks + 58) / 116;
}