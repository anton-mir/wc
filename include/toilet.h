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

class Toilet
{
    public:
    Toilet();

    void check_enter_pin();
    bool get_enter_btn_state();
    void set_enter_led(led_color light);
    void update_enter_led();
    void check_sleep();
    void check_sliv();
    void set_sleep(bool sleep_state);
    bool somebody_inside_toilet = false;
    bool door_is_blocked = false;

    private:
    bool sleep_mode = true; 
    bool blue_led_state = false;
};