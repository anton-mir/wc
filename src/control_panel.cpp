#include "control_panel.h"
#include "pitches.h"
#include "toneAC.h"
#include "ledstrip.h"
#include "toilet.h"
#include <RBD_Button.h>

extern LedStrip led_strip;
extern bool somebody_inside_toilet;

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
    set_panel_led(RED);
    digitalWrite(MAGNET, HIGH);
    toneAC(NOTE_C5, BUTTON_SOUND_VOLUME, BUTTON_SOUND_TIME, true);
    // blue_led_blink_timer.stop();
    somebody_inside_toilet = true;
    // sleep_mode = false;
  }
  if (switch_off.onPressed()) 
  {
    set_panel_led(GREEN);
    digitalWrite(MAGNET, LOW);
    toneAC(NOTE_A4, BUTTON_SOUND_VOLUME, BUTTON_SOUND_TIME, true);
    // blue_led_blink_timer.stop();
    somebody_inside_toilet = true;
    // sleep_mode = false;
  }
}

void ControlPanel::check_red_btn()
{
  if (red_big_btn.onPressed()) 
  {
    // blue_led_blink_timer.stop();  
    somebody_inside_toilet = true;
    // sleep_mode = false;
    toneAC(NOTE_E5, BUTTON_SOUND_VOLUME, BUTTON_SOUND_TIME, true);
    led_strip.ChangePaletteOneByOne();
  }
}