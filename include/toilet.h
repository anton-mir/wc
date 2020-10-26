#pragma once
#include <RBD_Button.h>
#include <RBD_Timer.h>
#include "main.h"

#define LED_GREEN   6
#define LED_RED     7
#define LED_BLUE    8
#define ENTER_BUTTON A1

class Toilet
{
    public:
    Toilet();

    void check_enter_pin();
    void set_enter_led(led_color light);
    void check_sleep();

    private:

};