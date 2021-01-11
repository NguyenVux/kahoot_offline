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

#define CHANNEL 10

unsigned long lastTime = 0;  
unsigned long timerDelay = 2000;  //send readings timer

typedef struct test_struct {
  int x;
  int y;
} test_struct;

test_struct myData;
//cái này bỏ có được ko 
uint8_t broadcastAddress[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus) {
  digitalWrite(LED, HIGH);
    Serial.print("Last Packet Send Status: ");
    if (sendStatus == 0){
      Serial.println("Delivery success");
    }
    else{
      Serial.println("Delivery fail");
    }
    digitalWrite(LED, LOW);
}

//callback function that will be executed when data is received
void OnDataRecv(uint8_t * mac, uint8_t *incomingData, uint8_t len) {
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
    // after timerDelay esp_now_send will trigger 
    //check if that is info from host 
    if(myData.x==0 && myData.y == 0)
        // lastTime = millis();
         sendit = false;
    digitalWrite(LED, LOW);
}

void setup() {
  //Initialize Serial Monitor
  Serial.begin(115200);
  pinMode(LED, OUTPUT); // set the digital pin as output.
  //Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  //Init ESP-NOW
  if (esp_now_init() != 0) {
      Serial.println("Error initializing ESP-NOW");
      return;
  }
  esp_now_set_self_role(ESP_NOW_ROLE_COMBO);
  esp_now_register_recv_cb(OnDataRecv);
  esp_now_register_send_cb(OnDataSent);
  //esp8266 do not have encrypt !!!
  esp_now_add_peer(broadcastAddress, ESP_NOW_ROLE_COMBO, CHANNEL, NULL, 0);
}

bool sendit = false;

void loop() {
  // if ((millis() - lastTime) == timerDelay) {
    // Set values to send
    myData.x = random(1,20);
    myData.y = random(1,20);

    // Send message via ESP-NOW
    // esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
    //if NULL then send to all address added by esp_now_add_peer 
    // but what if all node aslo get ms?
    if(!sendit)
    {
        sendit = true;
        esp_now_send(NULL, (uint8_t *) &myData, sizeof(myData));
    }

    // lastTime = millis();
  // }
}