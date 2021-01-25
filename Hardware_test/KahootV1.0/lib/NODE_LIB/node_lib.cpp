#include "node_lib.h"
#ifdef ESP8266

button_data ReadButtons(){

};

/*Cài đặt interrupt cho các nút nhấn*/
void setInterrupt(){

};

/*Huỷ Cài đặt interrupt cho các nút nhấn*/
void unsetInterrupt(){

};

/**
 * hàm nhận 
 * luôn lưu MAC_addr vào HOST_ADDR;
 * chớp đèn
*/
void OnDataRecv(uint8_t *mac, uint8_t *incomingData, uint8_t len)
{
    if (mode == PAIRING)
    {
        if (*incomingData == 0xff)
        {
            memcpy(Host_addr.address, mac, sizeof(Host_addr.address));
            if (!esp_now_add_peer(Host_addr.address, ESP_NOW_ROLE_MAX, 0, NULL, 0))
            {
                result = PAIRING_FAIL;
                mode = RUNNING;
            }
            else
            {
                PairSuccess();
            }
        }
    }
};

/**
 * Hàm gọi khi gửi, chớp đèn để biết là có gửi là ok
*/
void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus){

};

/**
 * Khi đọc được 2 nút nhấn đồng thời chuyển vào "chế độ nhận liên tục" từ bất kì node nào trong thời gian PAIR_TIME,
 * để phân biệt host thì data đọc được phải là 1 byte có giá trị 255.
 */
//chuyển vào "chế độ nhận liên tục"
void PairMode(){
    if(millis() - pairing_timer > PAIR_TIME)
    {
        mode = RUNNING;
        result = PARING_TIME_OUT;
    }
};

//thông báo(chớp led và buzz), Lưu HOST_ADDR và chuyển vào chế độ ngủ.
void PairSuccess(){
    mode = RUNNING;
    result = PARING_SUCCES;
};

//huỷ interrupt để khỏi gọi nữa, đọc giá trị các nút nhấn, gửi button_data cho host,setInterrupt lại ,sau đó ngủ tiếp
void OnWakeUp(){
    if(mode == RUNNING && result == PARING_SUCCES)
    {
        esp_now_send(Host_addr.address, &btn_data.button,sizeof(btn_data.button));
        ESP.deepSleep(0);
        OnWakeUp();
    }
};

/**
 * khởi tạo serial boardrate 115200
 * Đọc data HOST_ADDR từ epprom (6 byte đầu tiên)
 * Khởi tạo chế độ các nút nhấn
 * khởi tạo chế độ ngủ, setup interrupt các nút nhấn khi kích hoạt nút nhấn bất kì gọi hàm OnWakeUp; 
*/
void InitSys(){

};

#endif