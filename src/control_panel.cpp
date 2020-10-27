#include "control_panel.h"
#include "pitches.h"
#include "toneAC.h"
#include "ledstrip.h"
#include "toilet.h"
#include <RBD_Button.h>

extern LedStrip led_strip;
extern Toilet toilet;

RBD::Button switch_on(SWITCH_ON);
RBD::Button switch_off(SWITCH_OFF);
RBD::Button red_big_btn(RED_BIG_BUTTON);

ControlPanel::ControlPanel()
{
    pinMode(RED_BIG_BUTTON,INPUT_PULLUP);
    pinMode(MAGNET,OUTPUT);
    pinMode(LED_BOARD_GREEN,OUTPUT);
    pinMode(LED_BOARD_RED,OUTPUT);
    set_panel_led(GREEN);
    digitalWrite(MAGNET, LOW);
}

void ControlPanel::set_panel_led(led_color light)
{
  switch (light)
  {
    case RED:
      digitalWrite(LED_BOARD_RED,LOW);
      digitalWrite(LED_BOARD_GREEN,HIGH);
    break;
    case GREEN:
      digitalWrite(LED_BOARD_RED,HIGH);
      digitalWrite(LED_BOARD_GREEN,LOW);
    break;
    default:
      digitalWrite(LED_BOARD_RED,HIGH);
      digitalWrite(LED_BOARD_GREEN,HIGH);
    break;
  }
}

void ControlPanel::check_switch()
{
  if (switch_on.onPressed()) 
  {
    Serial.println(F("Switch on pressed"));
    toilet.set_sleep(false);
    toilet.update_enter_led();
    set_panel_led(RED);
    digitalWrite(MAGNET, HIGH);
    toneAC(NOTE_C5, BUTTON_SOUND_VOLUME, BUTTON_SOUND_TIME, true);
    toilet.somebody_inside_toilet = true;
  }
  if (switch_off.onPressed()) 
  {
    Serial.println(F("Switch off pressed"));
    toilet.set_sleep(false);
    toilet.update_enter_led();
    set_panel_led(GREEN);
    digitalWrite(MAGNET, LOW);
    toneAC(NOTE_A4, BUTTON_SOUND_VOLUME, BUTTON_SOUND_TIME, true);
    toilet.somebody_inside_toilet = true;
  }
}

void ControlPanel::check_red_btn()
{
  if (red_big_btn.onPressed()) 
  {
    Serial.println(F("Red button pressed"));
    toilet.set_sleep(false);
    toilet.update_enter_led();
    toneAC(NOTE_E5, BUTTON_SOUND_VOLUME, BUTTON_SOUND_TIME, true);
    led_strip.ChangePaletteOneByOne();
    toilet.somebody_inside_toilet = true;
  }
}