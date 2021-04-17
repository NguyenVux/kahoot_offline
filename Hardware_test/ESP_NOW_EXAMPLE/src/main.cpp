/*
This Code made by kahoot_offline team 7/1/2020
Note:
Code này dùng đẻ gửi hoặc nhận giữa 2 board esp
//source tham khảo
//https://randomnerdtutorials.com/esp-now-one-to-many-esp32-esp8266/
*/

//uncomment dòng này để lấy địa chỉ mac của host board
// #define GET_MAC_ADD
//comment dòng này để nạp cho mạch gửi (HOST)
//#define SENDER 

//2 cái thư viện của esp8266 và esp32 khác nhau cách sài nhé .... ghét thiệt

#include <Arduino.h>
#define WIFI_CHANNEL 6
#ifdef ESP8266
    #include <ESP8266WiFi.h>
    #include <espnow.h>
#elif ESP32
    #include <WiFi.h>
    #include <esp_now.h>
    //comment dòng này để nạp cho mạch gửi (HOST)
    #define SENDER 
#endif

//Structure example to receive data
//Must match the sender structure
typedef struct test_struct {
  int x;
  int y;
} test_struct;

test_struct myData;

#ifdef GET_MAC_ADD  
  void setup(){
    Serial.begin(115200);
    Serial.println();
    Serial.print("ESP Board MAC Address:  ");
    Serial.println(WiFi.macAddress());
  }
  void loop(){
  }
#else

#ifdef ESP8266
    #ifdef SENDER
        //sender
        uint8_t broadcastAddress[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
        // Create a struct_message called myData
        

        unsigned long lastTime = 0;  
        unsigned long timerDelay = 10;  // send readings timer

        // Callback when data is sent
        void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus) {
        Serial.print("Last Packet Send Status: ");
            if (sendStatus == 0){
                Serial.println("Delivery success");
            }
            else{
                Serial.println("Delivery fail");
            }
        }
        
        void setup() {
        // Init Serial Monitor
        Serial.begin(115200);
        WiFi.disconnect();
	    ESP.eraseConfig();
        delay(3000);

	    Serial.println(ESP.getSdkVersion());
        // Set device as a Wi-Fi Station
        WiFi.softAP("sender", "sendersender", WIFI_CHANNEL, false);
	    WiFi.mode(WIFI_AP_STA);
        WiFi.disconnect();
        // WiFi.mode(WIFI_STA);

        // Init ESP-NOW
        if (esp_now_init() != 0) {
            Serial.println("Error initializing ESP-NOW");
            return;
        }

        // Once ESPNow is successfully Init, we will register for Send CB to
        // get the status of Trasnmitted packet
        /*
        https://www.espressif.com/sites/default/files/documentation/esp-now_user_guide_en.pdf
            The peer's Role does not affect any
            function, but only stores the Role
            information for the application layer.
            LMAO
        */
        esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
        esp_now_register_send_cb(OnDataSent);
        
        // Register peer
        // esp_now_add_peer(broadcastAddress, ESP_NOW_ROLE_SLAVE, 6, NULL, 0);
        }
        int i = 0;
        void loop() {
            if ((millis() - lastTime) > timerDelay) {
                // Set values to send
                myData.x = i;//random(0,20);
                myData.y = i;//random(0,20);
                i++;
                // Send message via ESP-NOW
                Serial.println(i);
                esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
                //if NULL then send to all address added by esp_now_add_peer 
                // esp_now_send(NULL, (uint8_t *) &myData, sizeof(myData));

                lastTime = millis();
            }
            
        }
    #else
        uint8_t broadcastAddress[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
        //callback function that will be executed when data is received
        void OnDataRecv(uint8_t * mac, uint8_t *incomingData, uint8_t len) {
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
        }
        
        void setup() {
        //Initialize Serial Monitor
        Serial.begin(115200);
        WiFi.mode(WIFI_STA);
        WiFi.disconnect();
	    ESP.eraseConfig();
        delay(3000);
        //Set device as a Wi-Fi Station
        
        WiFi.begin("sender", "sendersender", WIFI_CHANNEL);
        WiFi.mode(WIFI_STA);
        WiFi.disconnect();
        // WiFi.softAP("sender", "sendersender", WIFI_CHANNEL, false);
        // WiFi.mode(WIFI_AP_STA);

        //Init ESP-NOW
        if (esp_now_init() != 0)
        {
            Serial.println("Error initializing ESP-NOW");
            return;
        }

            // Once ESPNow is successfully Init, we will register for recv CB to
            // get recv packer info
            esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
            // esp_now_set_self_role(ESP_NOW_ROLE_COMBO);
            // esp_now_add_peer(broadcastAddress, ESP_NOW_ROLE_CONTROLLER, WIFI_CHANNEL, NULL, 0);
            esp_now_register_recv_cb(OnDataRecv);
        }
        
        void loop() {

        }
    #endif
#endif

#ifdef ESP32
    #ifdef SENDER 
        // REPLACE WITH YOUR ESP RECEIVER'S MAC ADDRESS
        //bbroadcast
        uint8_t broadcastAddress1[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
        //unicast
        // uint8_t broadcastAddress2[] = {0xAF, 0xFA, 0xAF, 0xFA, 0xFF, 0xFB};
        // uint8_t broadcastAddress3[] = {0xDC, 0x4F, 0x22, 0x10, 0xD0, 0xD0};

        

        // callback when data is sent
        void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
            char macStr[18];
            Serial.print("Packet to: ");
            // Copies the sender mac address to a string
            snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
                    mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
            Serial.print(macStr);
            Serial.print(" send status:\t");
            Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
        }
        
        void setup() {
            Serial.begin(115200);
    
            WiFi.softAP("sender", "sendersender", WIFI_CHANNEL, false);
            // WiFi.mode(WIFI_STA);
            WiFi.mode(WIFI_AP_STA);
            WiFi.disconnect();
            
            if (esp_now_init() != ESP_OK) {
                Serial.println("Error initializing ESP-NOW");
                return;
            }
            
            esp_now_register_send_cb(OnDataSent);
            
            // register peer
            esp_now_peer_info_t peerInfo;
            peerInfo.channel = WIFI_CHANNEL;  
            peerInfo.encrypt = false;
            // register first peer  
            memcpy(peerInfo.peer_addr, broadcastAddress1, 6);
            if (esp_now_add_peer(&peerInfo) != ESP_OK){
                Serial.println("Failed to add peer");
                return;
            }
            // // register second peer  
            // memcpy(peerInfo.peer_addr, broadcastAddress2, 6);
            // if (esp_now_add_peer(&peerInfo) != ESP_OK){
            //     Serial.println("Failed to add peer");
            //     return;
            // }
            /// register third peer
            // memcpy(peerInfo.peer_addr, broadcastAddress3, 6);
            // if (esp_now_add_peer(&peerInfo) != ESP_OK){
            //     Serial.println("Failed to add peer");
            //     return;
            // }
        }
        int i = 0;
        unsigned long lastTime;
        
        void loop() {
            if ((millis() - lastTime) > 100) {
                myData.x = i;//random(0,20);
                myData.y = i;//random(0,20);
                i++;
                // esp_err_t result = esp_now_send(NULL, (uint8_t *) &myData, sizeof(test_struct));
                // esp_err_t result = esp_now_send(0, (uint8_t *) &myData, sizeof(test_struct));
                esp_err_t result = esp_now_send(broadcastAddress1, (uint8_t *) &myData, sizeof(test_struct));
                
                if (result == ESP_OK) {
                    Serial.println(i);
                    Serial.println("Sent with success");
                }
                else {
                    Serial.println("Error sending the data");
                }
                lastTime = millis();
            //delay(2000);
            }
        }
    #else
        //Create a struct_message called myData
        

        //callback function that will be executed when data is received
        void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
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
        }
        
        void setup() {
            //Initialize Serial Monitor
            Serial.begin(115200);
            
            //Set device as a Wi-Fi Station
            WiFi.mode(WIFI_STA);
            WiFi.disconnect();

            //Init ESP-NOW
            if (esp_now_init() != ESP_OK) {
                Serial.println("Error initializing ESP-NOW");
                return;
            }
            
            // Once ESPNow is successfully Init, we will register for recv CB to
            // get recv packer info
            esp_now_register_recv_cb(OnDataRecv);
        }
        
        void loop() {

        }
    #endif
#endif
#endif