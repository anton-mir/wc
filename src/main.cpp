#include "main.h"
#include "control_panel.h"
#include "toilet.h"
#include "ledstrip.h"

// ТУТ ТВОРИТСЯ МАГИЯ!!!
ControlPanel control_panel;
Toilet toilet;
LedStrip led_strip;

void setup() 
{
  Serial.begin(115200);
  Serial.println(F("Welcome to toilet!"));
}

void loop() 
{
  led_strip.run();
  control_panel.check_red_btn();
  control_panel.check_switch();
  toilet.check_enter_pin();
  toilet.check_sleep();
  
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
