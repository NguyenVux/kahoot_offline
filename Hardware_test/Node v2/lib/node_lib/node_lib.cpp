#include "node_lib.h"

#define toggle(x) digitalWrite(x,!digitalRead(x))

PAIR_STATUS pair_status = NOT_PAIRED;
void init_esp_now()
{
    WiFi.disconnect();
    ESP.eraseConfig();
    WiFi.mode(WIFI_STA);

    esp_now_init();
    esp_now_set_self_role(ESP_NOW_ROLE_COMBO);
    esp_now_register_recv_cb(onDataRecv);
    // esp_now_register_send_cb(onDataSent);    
 }

void init_interupt()
{
    pinMode(BUTTON_PIN::interupt_pin, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(BUTTON_PIN::interupt_pin), interupt, RISING);
}



void load_host_addr_from_eeprom()
{
    EEPROM.begin(6);
    EEPROM.get(0, Host_address);
    EEPROM.end();
    
    #ifdef DEBUG
        Serial.print("Host Addr: ");
        Serial.print(Host_address[0]);
        Serial.print(":");
        Serial.print(Host_address[1]);
        Serial.print(":");
        Serial.print(Host_address[2]);
        Serial.print(":");
        Serial.print(Host_address[3]);
        Serial.print(":");
        Serial.print(Host_address[4]);
        Serial.print(":");
        Serial.print(Host_address[5]);
    #endif
}

void check_if_paired()
{
    for(uint8_t i = 0; i < 6; i++)
    {
        if(Host_address.addr[i] != 0xff)
        {
            pair_status = PAIRED;
            return;
        }
    }
}
void save_host_addr_to_eeprom()
{
    EEPROM.begin(7);
    EEPROM.put(0, Host_address);
    EEPROM.end();
}

void init_data()
{
    load_host_addr_from_eeprom();
    check_if_paired();
}


void onDataRecv(uint8_t *mac, uint8_t *incomingData, uint8_t len)
{
    Serial.println("ON DATA");
    toggle(2);
}

void init_button()
{
    pinMode(BUTTON_PIN::btn1, INPUT_PULLUP);
    pinMode(BUTTON_PIN::btn2, INPUT_PULLUP);
    pinMode(BUTTON_PIN::btn3, INPUT_PULLUP);
    pinMode(BUTTON_PIN::btn4, INPUT_PULLUP);
}

void system_init()
{
    init_data();
    init_esp_now();
    if(pair_status == PAIRED)
    {
        esp_now_add_peer((Host_address.addr), ESP_NOW_ROLE_MAX, 0, NULL, 0);
    }
    init_button();
    init_interupt();
}

void pair()
{
    esp_now_add_peer((Host_address.addr), ESP_NOW_ROLE_MAX, 0, NULL, 0);
    state = STATE::RUNNING;
}

void ICACHE_RAM_ATTR interupt()
{
}