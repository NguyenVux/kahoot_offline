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

#define LED 2
#define CHANNEL 9

//Structure example to receive data
//Must match the sender structure
typedef struct test_struct {
  int x;
  int y;
} test_struct;

test_struct myData;

// REPLACE WITH YOUR ESP RECEIVER'S MAC ADDRESS
//bbroadcast
uint8_t broadcastAddress1[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

//callback function that will be executed when data is received
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
    digitalWrite(LED, HIGH);
    // In dia chi mac nhan duoc 
    char macStr[18];
    Serial.print("MacFrom");
    snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
            mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
    Serial.print(macStr);

    memcpy(&myData, incomingData, sizeof(myData));
    Serial.print("Bytes received: ");
    Serial.println(len);
    Serial.print("x: ");
    Serial.println(myData.x);
    Serial.print("y: ");
    Serial.println(myData.y);
    Serial.println();
    digitalWrite(LED, LOW);
}

// callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
    digitalWrite(LED, HIGH);
    char macStr[18];
    Serial.print("Packet to: ");
    // Copies the sender mac address to a string
    snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
            mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
    Serial.print(macStr);
    Serial.print(" send status:\t");
    Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
    digitalWrite(LED, LOW);
}

void setup() {
    Serial.begin(115200);
    pinMode(LED, OUTPUT); 
    WiFi.mode(WIFI_STA);
    
    if (esp_now_init() != ESP_OK) {
        Serial.println("Error initializing ESP-NOW");
        return;
    }
    
    esp_now_register_send_cb(OnDataSent);
    esp_now_register_recv_cb(OnDataRecv);
    
    // register peer
    esp_now_peer_info_t peerInfo;
    peerInfo.channel = CHANNEL;  
    peerInfo.encrypt = false;
    memcpy(peerInfo.peer_addr, broadcastAddress1, 6);
    // register first peer  
    if (esp_now_add_peer(&peerInfo) != ESP_OK){
        Serial.println("Failed to add peer");
        return;
    }

    // delay(2000);
    // //host identify 
    // myData.x = 0; //random(1,20);
    // myData.y = 0; //random(1,20);
    
    // esp_err_t result = esp_now_send(broadcastAddress1, (uint8_t *) &myData, sizeof(test_struct));
    // // esp_err_t result = esp_now_send(NULL, (uint8_t *) &myData, sizeof(test_struct));
    
    // if (result == ESP_OK) {
    //     Serial.println("Sent with success");
    // }
    // else {
    //     Serial.println("Error sending the data");
    // }
}

int i = 0;
unsigned long lastTime = 0;
unsigned long timerDelay = 2000; //send readings timer

void loop() {
    if ((millis() - lastTime) > timerDelay)
    {
        // Set values to send
        myData.x = i; //random(0,20);
        myData.y = i; //random(0,20);
        i++;
        // Send message via ESP-NOW
        Serial.println(i);
        esp_now_send(broadcastAddress1, (uint8_t *)&myData, sizeof(myData));
        //if NULL then send to all address added by esp_now_add_peer
        // esp_now_send(NULL, (uint8_t *) &myData, sizeof(myData));

        lastTime = millis();
    }
}