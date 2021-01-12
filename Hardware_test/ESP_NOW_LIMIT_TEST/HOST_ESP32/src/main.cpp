#include "WiFi.h"
#include "esp_now.h"

#define WIFI_CHANNEL 0
uint8_t broadcast_MAC[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};


void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

void setup()
{
    Serial.begin(115200);
    WiFi.mode(WIFI_MODE_STA);
    if (esp_now_init() != ESP_OK)
    {
        Serial.println("Error initializing ESP-NOW");
        return;
    }

    esp_now_peer_info_t peerInfo;
    memcpy(peerInfo.peer_addr, broadcast_MAC, 6);
    peerInfo.channel = WIFI_CHANNEL;
    peerInfo.encrypt = false;
    if (esp_now_add_peer(&peerInfo) != ESP_OK)
    {
        Serial.println("Failed to add peer");
        return;
    }
    esp_now_register_send_cb(OnDataSent);
}

void loop()
{

    uint8_t data = 255;
    

    esp_err_t result = esp_now_send(broadcast_MAC, &data, sizeof(data));

    if (result == ESP_OK)
    {
        Serial.println("Sent with success");
    }
    else
    {
        Serial.println("Error sending the data");
    }
    delay(2000);
}