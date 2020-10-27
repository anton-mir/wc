#pragma once
#include <RBD_Button.h>
#include <RBD_Timer.h>
#include "main.h"

#define LED_GREEN   6
#define LED_RED     7
#define LED_BLUE    8
#define ENTER_BUTTON A1
#define BLINK_DELAY 2000
#define SLEEP_DELAY 5000 

class Toilet
{
    public:
    Toilet();

    void check_enter_pin();
    void set_enter_led(led_color light);
    void update_enter_led();
    void check_sleep();
    void set_sleep(bool sleep_state);
    bool somebody_inside_toilet = false;

    private:
    bool sleep_mode = true; 
    bool blue_led_state = false;
};