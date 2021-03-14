// #include <header.h>
#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>
#include <Led.h>
Led main_led(2);
void (*state_loop)() = []() {};

void setup()
{
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

  if (esp_now_init() != ESP_OK)
  {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  main_led.blink(1000);


}

void loop()
{
  main_led.update();

  state_loop();
}