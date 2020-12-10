#include "control_panel.h"
#include "pitches.h"
#include "toneAC.h"
#include "ledstrip.h"
#include "toilet.h"
#include <RBD_Button.h>

extern LedStrip led_strip;
extern Toilet toilet;
extern RBD::Timer panel_blink_timer;

RBD::Button switch_close(SWITCH_OFF);
RBD::Button switch_open(SWITCH_ON);
RBD::Button red_big_btn(RED_BIG_BUTTON);

ControlPanel::ControlPanel()
{
    pinMode(RED_BIG_BUTTON,INPUT_PULLUP);
    pinMode(MAGNET,OUTPUT);
    pinMode(LED_BOARD_GREEN,OUTPUT);
    pinMode(LED_BOARD_RED,OUTPUT);
    set_panel_led(GREEN);
    digitalWrite(MAGNET, HIGH);
    panel_blink_timer.setTimeout(200);
    panel_blink_timer.stop();
}

void ControlPanel::set_panel_led(led_color light)
{
  switch (light)
  {
    case RED:
      digitalWrite(LED_BOARD_RED,HIGH);
      digitalWrite(LED_BOARD_GREEN,LOW);
      panel_leds_state = true;
    break;
    case GREEN:
      digitalWrite(LED_BOARD_RED,LOW);
      digitalWrite(LED_BOARD_GREEN,HIGH);
      panel_leds_state = true;
    break;
    case OFF:
      digitalWrite(LED_BOARD_RED,HIGH);
      digitalWrite(LED_BOARD_GREEN,HIGH);
      panel_leds_state = false;
    break;
    case ON:
      digitalWrite(LED_BOARD_RED,LOW);
      digitalWrite(LED_BOARD_GREEN,LOW);
      panel_leds_state = true;
    break;
    default:
      digitalWrite(LED_BOARD_RED,HIGH);
      digitalWrite(LED_BOARD_GREEN,HIGH);
      panel_leds_state = false;
    break;
  }
}

void ControlPanel::update_panel_led()
{
  if (switch_close.isPressed())
  {
    set_panel_led(RED);
  }
  else if (switch_open.isPressed())
  {
    set_panel_led(GREEN);
  }
}

void ControlPanel::check_switch()
{
  static bool click_helper = false;
  if (switch_close.onPressed()) 
  {
    Serial.println(F("Switch close is pressed"));
    toilet.set_sleep(false);
    toneAC(NOTE_C5, BUTTON_SOUND_VOLUME, BUTTON_SOUND_TIME, true);
    toilet.somebody_inside_toilet = true;
    if (toilet.get_enter_btn_state() && !click_helper)
    {
      digitalWrite(MAGNET, LOW);
      toilet.door_is_blocked = true;
      update_panel_led();
      Serial.println(F("Door is blocked"));
    }
  }
  if (switch_open.onPressed()) 
  {
    Serial.println(F("Switch open is pressed"));
    toilet.set_sleep(false);
    toneAC(NOTE_A4, BUTTON_SOUND_VOLUME, BUTTON_SOUND_TIME, true);
    toilet.somebody_inside_toilet = true;
    if (!toilet.door_is_blocked)
    {
      digitalWrite(MAGNET, HIGH);
      click_helper = false;
      update_panel_led();
    }
    else click_helper = true;
  }
}

void ControlPanel::check_red_btn()
{
  if (red_big_btn.onPressed()) 
  {
    Serial.println(F("Red button pressed"));
    toilet.set_sleep(false);
    toneAC(NOTE_E5, BUTTON_SOUND_VOLUME, BUTTON_SOUND_TIME, true);
    led_strip.ChangePaletteOneByOne();
    toilet.somebody_inside_toilet = true;
  }
}

void ControlPanel::run()
{
  check_red_btn();
  check_switch();
  
  // Panel led blinking logic
  if (panel_blink_timer.onExpired())
  {
    if (panel_blink_timer_counter--)
    {

        panel_leds_state ? set_panel_led(OFF) : set_panel_led(ON);
        panel_blink_timer.restart();
    }
    else
    {
      panel_blink_timer.stop();
      panel_blink_timer_counter = PANEL_BLINK_TIMES;
      if (toilet.door_is_blocked) 
        {
          Serial.println(F("Door is unblocked"));
          toilet.door_is_blocked = false;
          set_panel_led(RED);   
        }
    }
  }
}