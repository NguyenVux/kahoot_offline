/*
This Code made by kahoot_offline team 9/1/2020
FOR "NODE" 
Note:
Code này dùng để test số lượng node mà esp8266/esp32 có thể nhận trong cùng một thời điểm.

Để test:
1. Đầu tiên Node sẽ ở trong chế độ nhận
2. Sau khi nhận được tín hiệu "gửi đê" từ Host các node sẽ delay x giây (cần test) (để host chuyển sang chế độ nghe ngóng)
3. tất cả cùng một thời điểm spam thằng host xem nó có chịu nổi ko ...
*/
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <espnow.h>
#define LED 2
#define LED_ON digitalWrite(LED, LOW)
#define LED_OFF digitalWrite(LED, HIGH)

#define CHANNEL 9

unsigned long lastTime = 0;  
unsigned long timerDelay = 2000;  //send readings timer

uint8_t myData;
//cái này bỏ có được ko 
uint8_t broadcastAddress[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus) {
  //digitalWrite(LED, HIGH);
    Serial.print("Last Packet Send Status: ");
    if (sendStatus == 0){
      Serial.println("Delivery success");
    }
    else{
      Serial.println("Delivery fail");
    }
    //digitalWrite(LED, LOW);
}

unsigned long led_blink_ms = 0;
#define LED_BLINK_DELAY 1000

//callback function that will be executed when data is received
void OnDataRecv(uint8_t * mac, uint8_t *incomingData, uint8_t len) {
    //digitalWrite(LED, HIGH);
    // In dia chi mac nhan duoc 
    char macStr[18];
    Serial.print("MacFrom: ");
    snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
            mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
    Serial.println(macStr);

    // Serial.print("HOST MAC: ");
    // snprintf(macStr, sizeof(incomingData), "%02x:%02x:%02x:%02x:%02x:%02x",
    //          incomingData[0], incomingData[1], incomingData[2], incomingData[3], incomingData[4], incomingData[5]);
    // Serial.println(macStr);

    memcpy(&myData, incomingData, sizeof(myData));
    Serial.print("Bytes received: ");
    Serial.println(len);
    Serial.print("Data: ");
    Serial.println(myData);
    Serial.println();
    digitalWrite(LED, LOW);
    led_blink_ms = millis();
}

void setup() {
  //Initialize Serial Monitor
  Serial.begin(115200);
  //xoá các config cũ trong ESP !!!
  WiFi.disconnect();//will erase ssid/password
  delay(2000);
  ESP.eraseConfig();

  pinMode(LED, OUTPUT); // set the digital pin as output.
  //Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  //Init ESP-NOW
  if (esp_now_init() != 0) {
      Serial.println("Error initializing ESP-NOW");
      return;
  }
  esp_now_set_self_role(ESP_NOW_ROLE_COMBO);
  //esp8266 do not have encrypt !!!
  esp_now_add_peer(broadcastAddress, ESP_NOW_ROLE_COMBO, CHANNEL, NULL, 0);
  esp_now_register_send_cb(OnDataSent);
  esp_now_register_recv_cb(OnDataRecv);
}

int i = 0;
void loop() {
  // if(led_blink_ms > LED_BLINK_DELAY)
  //   LED_OFF;
  // if ((millis() - lastTime) > timerDelay)
  // {
  //   // Set values to send
  //   myData.x = i; //random(0,20);
  //   myData.y = i; //random(0,20);
  //   i++;
  //   // Send message via ESP-NOW
  //   Serial.println(i);
  //   esp_now_send(broadcastAddress, (uint8_t *)&myData, sizeof(myData));
  //   //if NULL then send to all address added by esp_now_add_peer
  //   // esp_now_send(NULL, (uint8_t *) &myData, sizeof(myData));

  //   lastTime = millis();
  // }
}