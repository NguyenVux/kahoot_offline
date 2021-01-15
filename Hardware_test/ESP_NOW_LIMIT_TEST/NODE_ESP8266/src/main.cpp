//#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <espnow.h>
#include "led.h"
Led LED_ON_BOARD(2);
uint8_t host_MAC[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
uint32_t delay_duration = 0;

void resetSettings()
{
    WiFi.mode(WIFI_STA);
#ifdef ESP32
    WiFi.disconnect(true, true);
#else
    WiFi.persistent(true);
    WiFi.disconnect(true);
    WiFi.persistent(false);
    //xoá các config cũ trong ESP !!!
    ESP.eraseConfig();
    delay(3000);
#endif
}

void OnRecv(uint8_t *mac, uint8_t *incomingData, uint8_t len)
{
    // if (!(strlen((char *)host_MAC)))
    // {
        memcpy(host_MAC, mac, 6);
        Serial.print("MAC ");
        for (int i = 0; i < 6; ++i)
        {
            Serial.print(": ");
            Serial.print(host_MAC[i], HEX);
        }
        // Serial.print("\nresult: ");
        // Serial.println(esp_now_add_peer(host_MAC, ESP_NOW_ROLE_SLAVE, 0, NULL, 0), DEC);
        // Serial.print("send result: ");
        // Serial.println(esp_now_send(host_MAC, incomingData, len), DEC);

        memcpy(&delay_duration,incomingData,len);
        if (delay_duration)
        {
            Serial.print("Delay Duration:  ");
            Serial.println(delay_duration);
            Serial.println("ON Data");
        }
        LED_ON_BOARD.blink(1000);
    // }
}

void onSent(uint8_t *mac_addr, uint8_t sendStatus)
{
    Serial.print("Status:");
    Serial.println(sendStatus ? "FAILED" : "SUCEED");
}
void setup()
{
    LED_ON_BOARD.blink(100);
    Serial.begin(115200);
    resetSettings();
    WiFi.mode(WIFI_STA);

    // WiFi.begin("sender", "sendersender",0);
    // WiFi.mode(WIFI_STA);
    // WiFi.disconnect();
    if (esp_now_init() != 0)
    {
        Serial.println("Failed to init");
        return;
    }
    esp_now_register_recv_cb(OnRecv);
    Serial.println("Registering send callback function");
    esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
    esp_now_register_send_cb(onSent);
}
uint64_t last_time = millis();
void loop()
{
    LED_ON_BOARD.update();
    uint64_t ctime = millis();
    if (delay_duration)
    {
        if (ctime - last_time >= delay_duration)
        {
            Serial.print("send result: ");
            esp_now_send(host_MAC, (uint8_t *)&ctime, sizeof(ctime));
            // esp_now_register_recv_cb(OnRecv);
            last_time = millis();
            // GỬI 1 LẦN
            delay_duration = 0;
            //LED_ON_BOARD.blink(100);
        }
    }
    // delay(100);
}