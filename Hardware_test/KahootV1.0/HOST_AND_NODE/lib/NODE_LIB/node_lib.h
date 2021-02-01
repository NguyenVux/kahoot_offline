/****
 *  By kahoot_offline team 11/1/2020
****/
#ifndef _NODE_LIB_
#define _NODE_LIB_
#ifdef ESP8266

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <espnow.h>
#include <TimerOne.h>
#include <EEPROM.h>
#define PAIR_TIME 60
#define LIGH_SLEEP_TIME_OUT 60
// #define PAIR_SUCCES 1
// #define PAIR_FAIL_TIME_OUT 2
// #define PAIRING 3
enum button_pin
{
    button1 = 12,
    button2,
    button3,
    button4,
};

enum MODE
{
    RUNNING,
    PAIRING
};

enum PAIRING_RESULT
{
    PAIRING_SUCCES,
    PAIRING_FAIL,
    PARING_TIME_OUT
};
uint64_t pairing_timer = 0;
uint64_t light_sleep_timer = 0;

/**
 * Struct này sync giữa host và node cho việc gửi nhận data
 * trong struct có 1 byte duy nhất, mỗi bit tương ứng với một nút nhấn
 * Hiện tại chúng ta có 4 nút nên bit 0,1,2,3 sẽ tương ứng với 4 nút nhấn 1:on 0:off
 * bit no: 7 6 5 4 3 2 1 0
 */
struct button_data
{
    uint8_t button;
};
//tradition of HCMUSssssss 
typedef struct button_data BUTTON_DATA;

/*
 *  struct chứa địa chỉ MAC 
*/
struct mac_addr
{
    uint8_t address[6];
};
//tradition of HCMUSssssss 
typedef struct mac_addr MAC_ADDR;

//địa chỉ của host
MAC_ADDR Host_addr;

/**
 * Đọc giá trị các nút nhấn
 */
button_data ReadButtons();
button_data btn_data;
/*Cài đặt interrupt cho các nút nhấn*/
void setInterrupt();

/*Huỷ Cài đặt interrupt cho các nút nhấn*/
void unsetInterrupt();

/**
 * hàm nhận 
 * luôn lưu MAC_addr vào HOST_ADDR;
 * chớp đèn
*/
void OnDataRecv(uint8_t * mac, uint8_t *incomingData, uint8_t len);

/**
 * Hàm gọi khi gửi, chớp đèn để biết là có gửi là ok
*/
void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus);

/**
 * Khi đọc được 2 nút nhấn đồng thời chuyển vào "chế độ nhận liên tục" từ bất kì node nào trong thời gian PAIR_TIME,
 * để phân biệt host thì data đọc được phải là 1 byte có giá trị 255.
 */

//int In_pair_mode = 0;
MODE mode = RUNNING;
PAIRING_RESULT result;
/* note: 
PAIR_SUCCES: đọc thành công
PAIR_FAIL_TIME_OUT: hết thời gian,  ngủ tiếp
PAIRING: đang chờ
*/
//chuyển vào "chế độ nhận liên tục"
void PairMode();

//thông báo(chớp led và buzz), Lưu HOST_ADDR và chuyển vào chế độ ngủ.
void PairSuccess();

//huỷ interrupt để khỏi gọi nữa, đọc giá trị các nút nhấn, gửi button_data cho host,setInterrupt lại ,sau đó ngủ tiếp
void OnWakeUp();

/**
 * khởi tạo serial boardrate 115200
 * Đọc data HOST_ADDR từ epprom (6 byte đầu tiên)
 * Khởi tạo chế độ các nút nhấn
 * khởi tạo chế độ ngủ, setup interrupt các nút nhấn khi kích hoạt nút nhấn bất kì gọi hàm OnWakeUp; 
*/
void InitSys();

#endif
#endif