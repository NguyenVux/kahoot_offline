#include <Arduino.h>
#include <node_lib.h>
#include <light_sleep.hpp>
#define DEBUG
void setup() {
  Serial.begin(112500);
  gpio_init();
  pinMode(2,OUTPUT);
  digitalWrite(2,LOW);
  system_init();
}

void loop() {
  init_esp_now();
  delay(200);
  Serial.println("Going to sleep now");
  light_sleep();
  delay(200);
  Serial.println("Wake up");
}