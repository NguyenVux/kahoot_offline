// #include <header.h>
#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>
#include <Led.h>
#include <StateBase.h>
Led main_led(2);
State state;

// check if there is any request from PC through Serial
bool listenRequest()
{
  return false;
}

// read request from PC
State::state_t readRequest()
{
  return State::Idle;
}

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
  if (listenRequest())
  {
    state.setCurState(readRequest());
  }
  main_led.update();
  state->loop();
}