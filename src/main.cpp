#include "main.h"

ControlPanel control_panel;
Tualet tualet;
LedStrip led_strip;

// ТУТ ТВОРИТСЯ МАГИЯ!!!

void Tualet::set_enter_led(ledcolor light)
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

void Tualet::check_enter_pin()
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
      // if (somebody_inside_toilet) {
      //   somebody_inside_toilet = false;
      //   sleep_timer.restart();
      // }
    }
}

void ControlPanel::set_panel_led(ledcolor light)
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
    // somebody_inside_toilet = true;
    // sleep_mode = false;
  }
  if (switch_off.onPressed()) 
  {
    set_panel_led(GREEN);
    digitalWrite(MAGNET, LOW);
    toneAC(NOTE_A4, BUTTON_SOUND_VOLUME, BUTTON_SOUND_TIME, true);
    // blue_led_blink_timer.stop();
    // somebody_inside_toilet = true;
    // sleep_mode = false;
  }
}

void ControlPanel::check_red_btn()
{
  if (red_big_btn.onPressed()) 
  {
    // blue_led_blink_timer.stop();  
    // somebody_inside_toilet = true;
    // sleep_mode = false;
    toneAC(NOTE_E5, BUTTON_SOUND_VOLUME, BUTTON_SOUND_TIME, true);
    led_strip.ChangePaletteOneByOne();
  }
}


void setup() 
{
  randomSeed(analogRead(A1));

  sleep_timer.setTimeout(10000);
  sleep_timer.stop();
  
  blue_led_blink_timer.setTimeout(3000);
  blue_led_blink_timer.restart();
}


void loop() 
{
  led_strip.run();
  control_panel.check_red_btn();
  control_panel.check_switch();
  tualet.check_enter_pin();
  
  // if (led_strip_on && !sleep_mode) actual_brightness = map(analogRead(KRUTILKA), 0, 1023, 0, 255);
  
  
  // if (sleep_timer.onExpired()) 
  // {
  //   tone(SOUND_PIN, NOTE_D2, 300);
  //   delay(300);
  //   noTone(SOUND_PIN);
  //   blue_led_blink_timer.restart();
  //   for (int i=actual_brightness; i==0; i--)
  //   {
  //     FastLED.setBrightness(i);
  //     FastLED.show();
  //     FastLED.delay(1000/UPDATES_PER_SECOND);
  //   }
  //   sleep_mode = true;
  // }

  // if (blue_led_blink_timer.onExpired())
  // {
  //   if (blue_led_state)
  //   {
  //     Tualet::set_enter_led(BLUE);
  //   }
  //   else
  //   {
  //     digitalWrite(LED_BLUE,HIGH);
  //     digitalWrite(LED_RED,HIGH);
  //     digitalWrite(LED_GREEN,HIGH);       
  //   }
  //   blue_led_blink_timer.restart();
  // }
}   
