#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <espnow.h>

uint8_t host_MAC[6] = {0x00,0x00,0x00,0x00,0x00,0x00};

void OnRecv(uint8_t *mac,uint8_t *incomingData, uint8_t len) {
    if(!(strlen((char *)host_MAC)))
    {
        memcpy(host_MAC,mac,6);
    }
}
void setup()
{
    Serial.begin(115200);
    WiFi.disconnect();
    ESP.eraseConfig();
    WiFi.mode(WIFI_STA);
    if(esp_now_init()!=0)
    {
        Serial.println("Failed to init");
        return;
    }
    esp_now_register_recv_cb(OnRecv);
    
}

void loop()
{

}