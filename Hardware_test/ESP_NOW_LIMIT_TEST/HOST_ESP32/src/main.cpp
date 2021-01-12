/*
This Code made by kahoot_offline team 9/1/2020
FOR "HOST" 
Note:
Code này dùng để test số lượng node mà esp8266/esp32 có thể nhận trong cùng một thời điểm.

Để test:
1. Đầu tiên HOST sẽ delay và boardcast tín hiệu nào đó ...
2. Chờ và nhận tín hiệu
*/

#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>
#include "led.h"

#define LED 2
#define CHANNEL 9
#define FIRST_BOARDCAST_TIMEOUT 1000

Led led(LED);
// Must match the sender structure
uint8_t myData;
// Broadcast MAC address
const uint8_t macAddr[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

// callback function that will be executed when data is received
void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len)
{
    // In dia chi mac nhan duoc
    char macStr[18];
    Serial.print("MacFrom");
    snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
             mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
    Serial.print(macStr);

    memcpy(&myData, incomingData, sizeof(myData));
    Serial.print("Bytes received: ");
    Serial.println(len);
    Serial.print("Data: ");
    Serial.println(myData);
    Serial.println();
}

// callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status)
{
    char macStr[18];
    Serial.print("Packet to: ");
    // Copies the sender mac address to a string
    snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
             mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
    Serial.print(macStr);
    Serial.print(" send status:\t");
    Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
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
    peerInfo.channel = CHANNEL;
    peerInfo.encrypt = false;
    memcpy(peerInfo.peer_addr, macAddr, 6);

    if (esp_now_add_peer(&peerInfo) != ESP_OK)
    {
        Serial.println("Failed to add peer");
        return;
    }
    
    led.blink(100);
    Serial.print("Broadcasting MAC address from ");
    Serial.println(WiFi.macAddress());
    uint8_t sendData = 0;
    unsigned long prevMilli = millis();
    //SPAMMING MAC ADDRESS
    while (millis() - prevMilli <= FIRST_BOARDCAST_TIMEOUT)
    {
        led.update();
        esp_now_send(macAddr, (uint8_t *)&sendData, sizeof(sendData));
        sendData++;
    }
    led.off();
}

int i = 0;
unsigned long lastTime = 0;
unsigned long timerDelay = 2000; //send readings timer

void loop()
{
    led.update();
    if ((millis() - lastTime) > timerDelay)
    {
        // Set values to send
        myData = i;
        i++;
        // Send message via ESP-NOW
        Serial.println(i);
        esp_now_send(macAddr, (uint8_t *)&myData, sizeof(myData));
        //if NULL then send to all address added by esp_now_add_peer
        // esp_now_send(NULL, (uint8_t *) &myData, sizeof(myData));

        lastTime = millis();
    }
}