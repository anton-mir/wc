#include "toilet.h"
#include "pitches.h"
#include "toneAC.h"

RBD::Timer sleep_timer;
RBD::Timer blue_led_blink_timer;

RBD::Button enter_btn(ENTER_BUTTON);

bool button_pressed_now, toilet_free, button_state_previous = 0;
unsigned long button_pressing_time = 0;

bool led_strip_on = true;

Toilet::Toilet()
{
    pinMode(LED_GREEN,OUTPUT);
    pinMode(LED_RED,OUTPUT);
    pinMode(LED_BLUE,OUTPUT);
    set_enter_led(GREEN);
    sleep_timer.setTimeout(SLEEP_DELAY);
    sleep_timer.restart();
    blue_led_blink_timer.setTimeout(BLINK_DELAY);
    blue_led_blink_timer.stop();
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
    case OFF:
    default:
      digitalWrite(LED_BLUE,HIGH);
      digitalWrite(LED_RED,HIGH);
      digitalWrite(LED_GREEN,HIGH);
    break;
  }
}

void Toilet::update_enter_led()
{
  enter_btn.isPressed() ? set_enter_led(RED) : set_enter_led(GREEN);
}

void Toilet::check_enter_pin()
{
  if (enter_btn.onPressed()) 
    {
      Serial.println(F("Enter the toilet"));
      set_sleep(false);
      toneAC(NOTE_GS5, BUTTON_SOUND_VOLUME, BUTTON_SOUND_TIME, true);
      update_enter_led();
      blue_led_blink_timer.stop();
    }
  if (enter_btn.onReleased())
    {
      Serial.println(F("Exit the toilet"));
      set_sleep(false);
      update_enter_led(); 
      toneAC(NOTE_GS4, BUTTON_SOUND_VOLUME, BUTTON_SOUND_TIME, true);
      blue_led_blink_timer.stop();
      if (somebody_inside_toilet) {
        somebody_inside_toilet = false;
        sleep_timer.restart();
      }
    }
}

void Toilet::set_sleep(bool sleep_state)
{
  if (sleep_state)
  {
     sleep_mode = true;
     blue_led_blink_timer.restart();
  }
  else
  {
     sleep_mode = false;
     blue_led_blink_timer.stop();
  } 
}

void Toilet::check_sleep()
{
  if (sleep_timer.onExpired())
  {
    set_sleep(true);
  }
  if (blue_led_blink_timer.onExpired() && sleep_mode)
  {
    blue_led_state ? set_enter_led(BLUE) : set_enter_led(OFF);
    blue_led_state = !blue_led_state;
    blue_led_blink_timer.restart(); 
  }
}