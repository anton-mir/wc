#include "toilet.h"
#include "pitches.h"
#include "toneAC.h"

RBD::Timer sleep_timer;
RBD::Timer blue_led_blink_timer;

RBD::Button enter_btn(ENTER_BUTTON);

bool button_pressed_now, toilet_free, button_state_previous = 0;
unsigned long button_pressing_time = 0;

bool led_strip_on = true;
bool somebody_inside_toilet = false;
// bool sleep_mode = false;
bool blue_led_state = false;

Toilet::Toilet()
{
    pinMode(LED_GREEN,OUTPUT);
    pinMode(LED_RED,OUTPUT);
    pinMode(LED_BLUE,OUTPUT);
    set_enter_led(GREEN);
    sleep_timer.setTimeout(300000);
    sleep_timer.stop();
    blue_led_blink_timer.setTimeout(3000);
    blue_led_blink_timer.restart();
}

void Toilet::set_enter_led(led_color light)
{
  switch (light)
  {
    case RED:
      digitalWrite(LED_BLUE,HIGH);
      digitalWrite(LED_RED,LOW);
      digitalWrite(LED_GREEN,HIGH);
    break;
    case GREEN:
      digitalWrite(LED_BLUE,HIGH);
      digitalWrite(LED_RED,HIGH);
      digitalWrite(LED_GREEN,LOW);
    break;
    case BLUE:
      digitalWrite(LED_BLUE,LOW);
      digitalWrite(LED_RED,HIGH);
      digitalWrite(LED_GREEN,HIGH);
    break;
    default:
      digitalWrite(LED_BLUE,HIGH);
      digitalWrite(LED_RED,HIGH);
      digitalWrite(LED_GREEN,HIGH);
    break;
  }
}

void Toilet::check_enter_pin()
{
  if (enter_btn.onPressed()) 
    {
      toneAC(NOTE_GS5, BUTTON_SOUND_VOLUME, BUTTON_SOUND_TIME, true);
      set_enter_led(RED);
      // blue_led_blink_timer.stop();
      // sleep_mode = false;
    }
  if (enter_btn.onReleased())
    {
      toneAC(NOTE_GS4, BUTTON_SOUND_VOLUME, BUTTON_SOUND_TIME, true);
      set_enter_led(GREEN); 
      // blue_led_blink_timer.stop();
      // sleep_mode = false;
      if (somebody_inside_toilet) {
        somebody_inside_toilet = false;
        sleep_timer.restart();
      }
    }
}

void Toilet::check_sleep()
{
  if (sleep_timer.onExpired())
  {
    set_enter_led(BLUE);
  }
}