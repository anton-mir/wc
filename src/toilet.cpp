#include "toilet.h"
#include "pitches.h"
#include "toneAC.h"
#include "ledstrip.h"

RBD::Timer sleep_timer;
RBD::Timer blue_led_blink_timer;
RBD::Button sliv(SLIV);
RBD::Button enter_btn(ENTER_BUTTON);

extern LedStrip led_strip;

Toilet::Toilet()
{
    pinMode(LED_GREEN,OUTPUT);
    pinMode(LED_RED,OUTPUT);
    pinMode(LED_BLUE,OUTPUT);
    // pinMode(SLIV,INPUT_PULLUP);
    set_enter_led(GREEN);
    sleep_timer.setTimeout(SLEEP_DELAY);
    sleep_timer.restart();
    blue_led_blink_timer.setTimeout(BLINK_DELAY);
    blue_led_blink_timer.stop();
    sliv.setDebounceTimeout(50);
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

bool Toilet::get_enter_btn_state()
{
  bool state = false;
  if (enter_btn.isPressed()) state = true;
  return state;
}

void Toilet::update_enter_led()
{
  enter_btn.isPressed() ? set_enter_led(RED) : set_enter_led(GREEN);
}

void Toilet::check_sliv()
{
  if (sliv.onPressed())
  {
    Serial.println(F("Sliv pressed"));
    if (door_is_blocked) 
    {
      Serial.println(F("Door is unblocked"));
      door_is_blocked = false;
    }
  }
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

void Toilet::set_sleep(bool state)
{
  if (state)
  {
     sleep_mode = true;
     blue_led_blink_timer.restart();
     led_strip.currentPalette = Black_p;
  }
  else if (sleep_mode)
  {
     Serial.println(F("Exit from the sleep mode"));
     sleep_mode = false;
     blue_led_blink_timer.stop();
     led_strip.ChangePaletteOneByOne();
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