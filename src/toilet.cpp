#include "toilet.h"
#include "control_panel.h"
#include "pitches.h"
#include "toneAC.h"
#include "ledstrip.h"

RBD::Timer sleep_countdown_timer;
RBD::Timer blue_led_blink_timer;
RBD::Timer panel_blink_timer;

RBD::Button sliv(SLIV);
RBD::Button enter_btn(ENTER_BUTTON);
RBD::Button body_movement(MOVEMENT_SENSOR);

extern LedStrip led_strip;
extern ControlPanel control_panel;

const uint8_t lights[360] = {
  0,   0,   0,   0,   0,   1,   1,   2, 
  2,   3,   4,   5,   6,   7,   8,   9, 
 11,  12,  13,  15,  17,  18,  20,  22, 
 24,  26,  28,  30,  32,  35,  37,  39, 
 42,  44,  47,  49,  52,  55,  58,  60, 
 63,  66,  69,  72,  75,  78,  81,  85, 
 88,  91,  94,  97, 101, 104, 107, 111, 
114, 117, 121, 124, 127, 131, 134, 137, 
141, 144, 147, 150, 154, 157, 160, 163, 
167, 170, 173, 176, 179, 182, 185, 188, 
191, 194, 197, 200, 202, 205, 208, 210, 
213, 215, 217, 220, 222, 224, 226, 229, 
231, 232, 234, 236, 238, 239, 241, 242, 
244, 245, 246, 248, 249, 250, 251, 251, 
252, 253, 253, 254, 254, 255, 255, 255, 
255, 255, 255, 255, 254, 254, 253, 253, 
252, 251, 251, 250, 249, 248, 246, 245, 
244, 242, 241, 239, 238, 236, 234, 232, 
231, 229, 226, 224, 222, 220, 217, 215, 
213, 210, 208, 205, 202, 200, 197, 194, 
191, 188, 185, 182, 179, 176, 173, 170, 
167, 163, 160, 157, 154, 150, 147, 144, 
141, 137, 134, 131, 127, 124, 121, 117, 
114, 111, 107, 104, 101,  97,  94,  91, 
 88,  85,  81,  78,  75,  72,  69,  66, 
 63,  60,  58,  55,  52,  49,  47,  44, 
 42,  39,  37,  35,  32,  30,  28,  26, 
 24,  22,  20,  18,  17,  15,  13,  12, 
 11,   9,   8,   7,   6,   5,   4,   3, 
  2,   2,   1,   1,   0,   0,   0,   0, 
  0,   0,   0,   0,   0,   0,   0,   0, 
  0,   0,   0,   0,   0,   0,   0,   0, 
  0,   0,   0,   0,   0,   0,   0,   0, 
  0,   0,   0,   0,   0,   0,   0,   0, 
  0,   0,   0,   0,   0,   0,   0,   0, 
  0,   0,   0,   0,   0,   0,   0,   0, 
  0,   0,   0,   0,   0,   0,   0,   0, 
  0,   0,   0,   0,   0,   0,   0,   0, 
  0,   0,   0,   0,   0,   0,   0,   0, 
  0,   0,   0,   0,   0,   0,   0,   0, 
  0,   0,   0,   0,   0,   0,   0,   0, 
  0,   0,   0,   0,   0,   0,   0,   0, 
  0,   0,   0,   0,   0,   0,   0,   0, 
  0,   0,   0,   0,   0,   0,   0,   0, 
  0,   0,   0,   0,   0,   0,   0,   0
};

Toilet::Toilet()
{
    pinMode(LED_GREEN,OUTPUT);
    pinMode(LED_RED,OUTPUT);
    pinMode(LED_BLUE,OUTPUT);
    set_enter_led(GREEN);
    sleep_countdown_timer.setTimeout(SLEEP_DELAY);
    sleep_countdown_timer.restart();
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

bool Toilet::enter_door_closed()
{
  bool state = false;
  if (enter_btn.isPressed()) state = true;
  return state;
}

void Toilet::update_enter_led()
{
  if (enter_btn.isPressed() && somebody_inside_toilet)
  {
    set_enter_led(RED);
  }
  else if (!sleep_mode_active)
  {
    set_enter_led(GREEN);
  }
}

void Toilet::check_sliv()
{
  if (sliv.onPressed())
  {
    Serial.println(F("Sliv pressed"));
    toneAC(NOTE_GS4, BUTTON_SOUND_VOLUME, BUTTON_SOUND_TIME, true);
    control_panel.set_panel_led(OFF);
    panel_blink_timer.restart();
    set_sleep(false);
  }
}

void Toilet::check_enter_pin()
{
  if (enter_btn.onPressed()) 
    {
      Serial.println(F("Enter the toilet"));
      // set_sleep(false);
      toneAC(NOTE_GS5, BUTTON_SOUND_VOLUME, BUTTON_SOUND_TIME, true);
      update_enter_led();
      blue_led_blink_timer.stop();
    }
  if (enter_btn.onReleased())
    {
      Serial.println(F("Exit the toilet"));
      // set_sleep(false);
      update_enter_led(); 
      toneAC(NOTE_GS4, BUTTON_SOUND_VOLUME, BUTTON_SOUND_TIME, true);
      blue_led_blink_timer.stop();
      sleep_countdown_timer.restart();
    }
}

void Toilet::set_sleep(bool enter_sleep_mode)
{
  if (enter_sleep_mode)
  {
     sleep_mode_active = true;
     blue_led_blink_timer.restart();
     led_strip.currentPalette = Black_p;
  }
  else 
  {
    if (sleep_mode_active)
    {
      Serial.println(F("Exit from the sleep mode"));
      sleep_mode_active = false;
      blue_led_blink_timer.stop();
      led_strip.ChangePaletteOneByOne();
      if (!enter_door_closed())
      {
        sleep_countdown_timer.restart();
      }
    }
    somebody_inside_toilet = true;
  }
}

void Toilet::randomColourEnterLed()
{
    byte random_led_number, second_led_number, zero_led_number, random_led_power, second_led_power;

    random_led_number = random(0,3);
    second_led_number = (random_led_number + 1) % 3;
    zero_led_number = (random_led_number + 2) % 3;

    random_led_power=random(0,256);
    second_led_power = (random_led_power + random(0,100)) % 255;

    leds[random_led_number]=lights[random_led_power];
    leds[second_led_number]=lights[second_led_power];
    leds[zero_led_number]=0;

    analogWrite(LED_RED,leds[0]);
    analogWrite(LED_GREEN,leds[1]);
    analogWrite(LED_BLUE,leds[2]);
}

void Toilet::check_sleep()
{
  if (sleep_countdown_timer.onExpired() && !somebody_inside_toilet)
  {
    set_sleep(true);
  }
  if (blue_led_blink_timer.onExpired() && sleep_mode_active)
  {
    blue_led_state ? set_enter_led(BLUE) : set_enter_led(GREEN);
    blue_led_state = !blue_led_state;
    blue_led_blink_timer.restart(); 
  }
}

void Toilet::check_body_movement()
{
  if (body_movement.onReleased())
    {
      Serial.println(F("Body inside toilet is moving!"));
      set_sleep(false);
    }
  if (body_movement.onPressed())
    {
      Serial.println(F("No body inside toilet :("));
      somebody_inside_toilet = false;
      sleep_countdown_timer.restart();
    }
}

void Toilet::check_light()
{
  if (!light_is_on && analogRead(LIGHT_SENSOR) < 800) 
  {
    Serial.println(F("Light was turned ON"));
    light_is_on = true;
    set_sleep(false);
  }
  else if (light_is_on && analogRead(LIGHT_SENSOR) >= 800)
  {
    Serial.println(F("Light was turned OFF"));
    light_is_on = false;
    somebody_inside_toilet = false;
    sleep_countdown_timer.restart();
  }
}

void Toilet::run()
{
  check_sliv();
  check_enter_pin();
  check_sleep();
  update_enter_led();
  check_body_movement();
  check_light();
}