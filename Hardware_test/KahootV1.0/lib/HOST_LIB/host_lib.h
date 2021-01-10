/****
 *  By kahoot_offline team 11/1/2020
****/
#ifndef _HOST_LIB_
#define _HOST_LIB_
#ifdef ESPP32

#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>

//thời gian đang tính theo giây nhé các bạn tuỳ ý chỉnh sửa
#define BOARD_CAST_TIME 60
#define BOARD_CAST_INTERVAL 2
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
//note: với host thì 2 cái truct này có thể để note chơi thôi ...

/**
 * hàm chờ nhận tín hiệu,
 * khi nhận được gửi qua serial theo struct sau:
 * Tín hiệu gửi qua serial gồm 8 byte có cấu trúc như sau:
 * byte:     0       1       2       3       4       5       6       7
 *   ex:  0xFA    0xAA    0xAA    0xAA    0xAA    0xAA    0x01     '\n'
 * byte 0 -> 5: [-------------Địa chỉa mac--------------------] 
 * byte 6:      [byte chứa thông tin nút nhấn]
 * byte 7:      [tín hiệu '\n' kết thúc]
*/
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len);

/**
 * Hàm dùng để board cast MAC của host trong vòng BOARD_CAST_TIME, mỗi BOARD_CAST_INTERVAL sẽ gửi tín hiệu 1 lần
 * Note lúc này OnDataRecv vẫn chạy
*/
void Pairing();

/**
 * hàm khởi tạo serial boardrate 115200
 * khởi tạo chế độ nhận data 
*/
void InitSys();

#endif
#endif