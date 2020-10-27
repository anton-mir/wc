#pragma once
#include "Arduino.h"

#define SOUND_PIN1 9
#define SOUND_PIN2 10
#define BUTTON_SOUND_TIME 300
#define BUTTON_SOUND_VOLUME 10

typedef enum led_light
{
    RED = 0,
    GREEN,
    BLUE,
    OFF
} led_color;
