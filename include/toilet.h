#pragma once
#include <RBD_Button.h>
#include <RBD_Timer.h>
#include "main.h"

#define LED_GREEN   6
#define LED_RED     7
#define LED_BLUE    8
#define SLIV A2
#define BLINK_DELAY 2000
#define SLEEP_DELAY 300000 
#define ENTER_BUTTON A1
#define MOVEMENT_SENSOR A3
#define LIGHT_SENSOR A4

class Toilet
{
    public:
    Toilet();

    void check_enter_pin();
    void check_body_movement();
    void randomColourEnterLed();
    bool enter_door_closed();
    void set_enter_led(led_color light);
    void update_enter_led();
    void check_sleep();
    void check_sliv();
    void check_light();
    void set_sleep(bool sleep_state);
    bool somebody_inside_toilet = false;
    bool door_is_blocked = false;
    void run();

    private:
    bool light_is_on = false;
    bool sleep_mode_active = true; 
    bool blue_led_state = false;
    uint16_t leds[3], color[3];
};