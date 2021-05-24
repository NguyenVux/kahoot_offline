#include <Arduino.h>
#include <ESP8266WiFi.h>
// Required for LIGHT_SLEEP_T delay mode
extern "C" {
   #include "user_interface.h"
}
extern "C" {
   #include "gpio.h"
 }

void light_sleep();