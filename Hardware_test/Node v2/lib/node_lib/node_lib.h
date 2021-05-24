#ifndef _NODE_LIB_H
#define _NODE_LIB_H

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <espnow.h>
#include <EEPROM.h>

#define DONE 1
#define FAILED 0

#define PAIR_TIME
#define LIGHT_SLEEP_TIME_OUT


#define PAIR_STATUS bool
#define PAIRED true
#define NOT_PAIRED false


enum STATE
{
    RUNNING,
    PAIRING,
    OTA
};

extern STATE state;

enum BUTTON_PIN
{
    btn1 = 12,
    btn2,
    btn3,
    btn4 ,
    interupt_pin = 5
};



volatile struct
{
    uint8_t data;
} button_data = {0b0001000};





extern PAIR_STATUS pair_status;


struct
{
    uint8_t addr[6];
} Host_address = {0xff,0xff,0xff,0xff,0xff,0xff};


void init_esp_now();
void init_interupt();
void init_data();
void system_init();
void load_host_addr_from_eeprom();
void save_host_addr_to_eeprom();
void check_if_paired();
void init_button();
void onDataRecv(uint8_t *mac, uint8_t *incomingData, uint8_t len);
void ICACHE_RAM_ATTR interupt();

#endif /* GRANDPARENT_H */