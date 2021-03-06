#include <header.h>
#include <SerialIO.h>
#include <./State/State.h>
Led main_led(2);
State state;

void setup()
{
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

  if (esp_now_init() != ESP_OK)
  {
    Serial.println("[ERROR] Initialize ESP-NOW failed");
    return;
  }
  main_led.blink(1000);
}

void loop()
{
  main_led.update();

  if (Serial.available())
  {
    SerialHeader header;
    if (!parseHeader(header, Serial))
      Serial.println("[ERROR] Cannot parse Serial header");
    else
    {
      state.setCurState(header.changeState);
      //TODO: Handle fallback if reset state failed
      //31.3.2021: ALWAYS RESET STATE TO SET SEND/RECV CALLBACK FUNCTION
      if (header.resetState)
      {
        state.resetCurState();
        state->init();
      }
    }
    Serial.flush(); //Not sure about this, but just for precaution
  }
  else
  {
    state->loop();
  }
}