/*
This Code made by kahoot_offline team 9/1/2020
FOR "HOST" 
Note:
Code này dùng để test số lượng node mà esp8266/esp32 có thể nhận trong cùng một thời điểm.
*/

#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>
#include "led.h"
#include "broadcast.h"
#include "client.h"
#include "util.h"

#define CHANNEL 0
#define LISTEN_BROADCAST_REPLY_TIMEOUT 10000

// Broadcast MAC address
uint8_t macAddr[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

void serialPrintMAC(const uint8_t *addr)
{
    char str[18];
    snprintf(str, sizeof(str), MACSTR,
             MAC2STR(addr));
    Serial.print(str);
}

void registerClient(const uint8_t *mac, const uint8_t *incomingData, int len)
{
    //CHUA THONG NHAT CACH TAO ID, NEN ID = 0
    if (!client::search(mac))
    {
        client::add(mac, 0);
        Serial.print("NEW CLIENT: ");
    }
    else
    {
        Serial.print("DUPLICATE: ");
    }
    serialPrintMAC(mac);
    Serial.println();
}

void receiveAnswer(const uint8_t *mac, const uint8_t *incomingData, int len)
{

}

void waitReply(size_t mili)
{
    Stopwatch<> waitReply;
    waitReply.start();
    while (waitReply.elapsed() <= LISTEN_BROADCAST_REPLY_TIMEOUT)
        ;
    Serial.print("TOTAL: ");
    Serial.print(client::size());
    Serial.println();
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

    esp_now_register_recv_cb(registerClient);

    startBroadcast(macAddr, (uint8_t *)&sendData, sizeof(sendData));
    waitReply(LISTEN_BROADCAST_REPLY_TIMEOUT);

    esp_now_register_recv_cb(receiveAnswer);
}
void loop()
{
}