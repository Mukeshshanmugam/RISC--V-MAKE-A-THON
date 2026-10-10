#include <stdint.h>

#include "gpio.h"
#include "timer.h"
#include "ultrasonic.h"
#include "7segment.h"
#include "buzzer.h"
#include "indicator.h"

// Distance thresholds in cm
#define SAFE_CM       30
#define CAUTION_CM    15
#define STOP_CM        5

// One loop step in milliseconds (HC-SR04 needs at least 60 ms between measurements)
#define STEP_MS      100

// Seven-segment pattern for "-" (common-cathode assumed)
#define SEG_DASH      0x40

// Application states
enum
{
    ST_SAFE,
    ST_CAUTION,
    ST_WARNING,
    ST_STOP,
    ST_SENSOR_ERROR
};

static uint8_t state      = ST_SAFE;
static uint8_t last_state = 0xFF;
static uint8_t beep_step  = 0;

// Show two segment patterns on two separate displays
void show_pattern(uint8_t tens, uint8_t units)
{
    *DAT[A] = tens;            // tens display on Port A
    *DAT[C] = units;           // units display on Port C
}

void show_number(uint16_t value)
{
    if (value > 99)
    {
        value = 99;
    }

    show_pattern(a[value / 10], a[value % 10]);
}

// Display a sensor error: --
void show_error(void)
{
    show_pattern(SEG_DASH, SEG_DASH);
}

// Decide the application state from the distance
uint8_t decide_state(uint16_t dist)
{
    if (dist > SAFE_CM)
        return ST_SAFE;

    if (dist >= CAUTION_CM)
        return ST_CAUTION;

    if (dist >= STOP_CM)
        return ST_WARNING;

    return ST_STOP;
}

void setup(void)
{
    Serial.begin(9600);        // optional: prints the distance for checking

    config_reg(A, OUT);        // tens display
    config_reg(C, OUT);        // units display

    indicator_init();
    ultra_init();
    buzzer_init();

    show_number(88);           // start-up test: all segments should light
    Delay_Millsec(1000);
}

void loop(void)
{
    uint16_t dist = ultra_get_distance_cm();

    Serial.println(dist);      // optional: 65535 means no echo

    // Only a missing echo is an error. Large distances are valid (SAFE).
    if (dist == ULTRA_ERROR)
        state = ST_SENSOR_ERROR;
    else
        state = decide_state(dist);

    if (state != last_state)
        beep_step = 0;         // restart the beep pattern

    switch (state)
    {
        case ST_SAFE:
            indicator_set_zone(ZONE_SAFE);
            buzzer_off();
            show_number(dist);
            break;

        case ST_CAUTION:       // slow beep: 200 ms on, 600 ms off
            indicator_set_zone(ZONE_CAUTION);
            show_number(dist);
            if (beep_step == 0) buzzer_on(2000);
            if (beep_step == 2) buzzer_off();
            beep_step = (beep_step + 1) % 8;
            break;

        case ST_WARNING:       // faster beep: 100 ms on, 100 ms off
            indicator_set_zone(ZONE_WARNING);
            show_number(dist);
            if (beep_step == 0) buzzer_on(2500);
            if (beep_step == 1) buzzer_off();
            beep_step = (beep_step + 1) % 2;
            break;

        case ST_STOP:          // continuous tone
            indicator_set_zone(ZONE_STOP);
            show_number(dist);
            if (state != last_state) buzzer_on(3000);
            break;

        case ST_SENSOR_ERROR:
        default:
            indicator_set_zone(ZONE_NONE);
            buzzer_off();
            show_error();      // -- = no echo received
            break;
    }

    last_state = state;
    Delay_Millsec(STEP_MS);
}