/****
 *  By kahoot_offline team 11/1/2020
****/
#include "host_lib.h"
#ifdef ESP32
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
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len)
{

}

/**
 * Hàm dùng để board cast MAC của host trong vòng BOARD_CAST_TIME
 * Note lúc này OnDataRecv vẫn chạy để xem coi ai đã pair rồi 
*/
void Pairing()
{

}
/**
 * hàm khởi tạo serial boardrate 115200
 * khởi tạo chế độ nhận data 
*/
void InitSys()
{

}

#endif