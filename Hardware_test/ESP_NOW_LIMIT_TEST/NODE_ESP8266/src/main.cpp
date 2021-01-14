//#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <espnow.h>

uint8_t host_MAC[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
int delay_duration = 0;
void OnRecv(uint8_t *mac, uint8_t *incomingData, uint8_t len)
{
    if (!(strlen((char *)host_MAC)))
    {
        memcpy(host_MAC, mac, 6);
        Serial.print("MAC ");
        for (int i = 0; i < 6; ++i)
        {
            Serial.print(": ");
            Serial.print(host_MAC[i], HEX);
        }
        Serial.print("result: ");
        Serial.println(esp_now_add_peer(host_MAC, ESP_NOW_ROLE_SLAVE, 0, NULL, 0), DEC);
        Serial.print("send result: ");
        Serial.println(esp_now_send(host_MAC, incomingData, len), DEC);

        memcpy(&delay_duration,incomingData,len);
        if (delay_duration)
        {
            Serial.print("Delay Duration:  ");
            Serial.println(delay_duration);
            Serial.println("ON Data");
        }
    }
}

void onSent(uint8_t *mac_addr, uint8_t sendStatus)
{
    Serial.print("Status:");
    Serial.println(sendStatus?"FAILED":"SUCEED");
}
void setup()
{
    Serial.begin(115200);

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
    uint64_t ctime = millis();
    if(delay_duration)
    {
        if(ctime - last_time >= delay_duration)
        {
            esp_now_send(host_MAC,(uint8_t *)&ctime, sizeof(ctime));
            last_time = millis();   
            // GỬI 1 LẦN 
            delay_duration = 0;
        }
    }
}