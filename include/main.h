#include "Arduino.h"
#include <RBD_Timer.h>
#include <RBD_Button.h>
#include "pitches.h"
#include "ledstrip.h"
#include "toneAC.h"

#define SOUND_PIN1 9
#define SOUND_PIN2 10
#define BUTTON_SOUND_TIME 300
#define BUTTON_SOUND_VOLUME 10
#define RED_BIG_BUTTON 4
#define LED_GREEN   6
#define LED_RED     7
#define LED_BLUE    8
#define ENTER_BUTTON A1
#define LED_BOARD_RED 12
#define LED_BOARD_GREEN 13
#define MAGNET 3
#define SWITCH_ON 2
#define SWITCH_OFF 11

RBD::Timer sleep_timer;
RBD::Timer blue_led_blink_timer;
RBD::Button enter_btn(ENTER_BUTTON);
RBD::Button red_big_btn(RED_BIG_BUTTON);
RBD::Button switch_on(SWITCH_ON);
RBD::Button switch_off(SWITCH_OFF);

bool button_pressed_now, toilet_free, button_state_previous = 0;
unsigned long button_pressing_time = 0;

bool led_strip_on = true;
// bool somebody_inside_toilet = false;
// bool sleep_mode = false;
bool blue_led_state = false;

typedef enum led_light
{
    RED = 0,
    GREEN,
    BLUE
} ledcolor;

class Tualet
{
    public:
    Tualet()
    {
        pinMode(LED_GREEN,OUTPUT);
        pinMode(LED_RED,OUTPUT);
        pinMode(LED_BLUE,OUTPUT);
        set_enter_led(GREEN);
    }

    void check_enter_pin();
    void set_enter_led(ledcolor light);

    private:

};

class ControlPanel
{
    public:
    ControlPanel()
    {
        pinMode(RED_BIG_BUTTON,INPUT_PULLUP);
        pinMode(MAGNET,OUTPUT);
        pinMode(LED_BOARD_GREEN,OUTPUT);
        pinMode(LED_BOARD_RED,OUTPUT);
        set_panel_led(GREEN);
        digitalWrite(MAGNET, LOW);
    }

    void check_switch();
    void check_red_btn();
    void set_panel_led(ledcolor light);

    private:
};
