/*
This Code made by kahoot_offline team 9/1/2020
FOR "HOST" 
Note:
Code này dùng để test số lượng node mà esp8266/esp32 có thể nhận trong cùng một thời điểm.

Để test:
1. Đầu tiên HOST sẽ delay và boardcast tín hiệu nào đó ...
2. Chờ và nhận tín hiệu
*/

// #include <Arduino.h>
// #include <WiFi.h>
// #include <esp_now.h>
// #include "led.h"
// #include "stopwatch.h"
#include "broadcast.h"
#include "client.h"

#define LED 2
#define CHANNEL 0

// Led led(LED);
// Broadcast MAC address
uint8_t macAddr[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

// callback function that will be executed when data is received
// void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len)
// {
//     // In dia chi mac nhan duoc
//     char macStr[18];
//     Serial.print("MacFrom");
//     snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
//              mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
//     Serial.print(macStr);

//     //memcpy(&myData, incomingData, sizeof(myData));
//     Serial.print("Bytes received: ");
//     Serial.println(len);
//     Serial.print("Data: ");
//     //Serial.println(myData);
//     Serial.println();
// }

// callback when data is sent
// void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status)
// {
//     char macStr[18];
//     Serial.print("Packet to: ");
//     // Copies the sender mac address to a string
//     snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
//              mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
//     Serial.print(macStr);
//     Serial.print(" send status:\t");
//     Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
// }

void receiveReply(const uint8_t *mac, const uint8_t *incomingData, int len)
{
    //CHUA THONG NHAT CACH TAO ID, NEN DE TRONG
    addClient(mac, 0);
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

    // Prepare to broadcast this MAC address
    esp_now_peer_info_t peerInfo;
    memcpy(peerInfo.peer_addr, macAddr, 6);
    peerInfo.channel = CHANNEL;
    peerInfo.encrypt = false;

    if (esp_now_add_peer(&peerInfo) != ESP_OK)
    {
        Serial.println("Failed to add peer");
        return;
    }

    Serial.print("Broadcasting MAC address from ");
    Serial.println(WiFi.macAddress());
    auto sendData = DEFAULT_BROADCAST_TIMEOUT;

    esp_now_register_recv_cb(receiveReply);
    startBroadcast(macAddr, (uint8_t *)&sendData, sizeof(sendData));
}

int lastsize = 0;
void loop()
{
    if (lastsize != clientSize())
    {
        Serial.print("Found: no.");
        Serial.print(lastsize);
        Serial.print(" MAC ");
        // for (int i = 0; i < 6; ++i)
        // {
        //     Serial.print(":");
        //     Serial.print(ClientInfo()[lastsize].macAddr[i], HEX);
        // }
        char str[18];
        auto *c = ClientInfo()[lastsize].macAddr;
        snprintf(str, sizeof(str), "%02x:%02x:%02x:%02x:%02x:%02x",
                 c[0], c[1], c[2], c[3], c[4], c[5]);
        Serial.print(str);
        Serial.println();
        lastsize++;
    }
}