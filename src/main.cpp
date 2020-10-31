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
  toilet.check_sliv();
  toilet.check_enter_pin();
  toilet.check_sleep();
}   
