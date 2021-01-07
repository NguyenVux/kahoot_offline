/*
This Code made by kahoot_offline team 7/1/2020
Note:
0. Code dùng để communicate giữa 2 board esp bằng BLE
1. Master/Slave mình nghĩ nên dùng precomplite(#ifdef) để khỏi có quá nhiều file nha
2. giới thiệu về BLE: https://www.electronics-lab.com/project/using-the-ble-functionality-of-the-esp32/ tuy nhiên trong khi sài thì có thể sài các thư viện build sẵn (các giải pháp mình nêu ra trong phần 3)
3. Cái này mn lưu ý có 3 giải pháp nhỏ mình đang care là sài 
doc:
// https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/bluetooth/index.html
A. BLE connect Peer-to-Peer
  todo: 1. Maxconnection của boardcast ~6 ?

B. BLE connect Boardcast
  todo: 2. Maxconnection của boardcast chưa rõ

C. BLE BOARDCAST

D.  TỰ tụi mình làm một cái protocal riêng sử dụng BLE ...

cái này lạ lạ :D
https://www.instructables.com/Multiple-ITags-With-ESP32/
*/

// more info
// https://github.com/CrazyRobMiles/SimpleESP32BluetoothBLE
// some examble code
// https://github.com/nkolban/ESP32_BLE_Arduino/blob/master/examples/BLE_server_multiconnect/BLE_server_multiconnect.ino
//source from https://github.com/nkolban/ESP32_BLE_Arduino/tree/master/examples

// chưa biết sài cái nàu, thật á

#include <Arduino.h>

void setup() {
  // put your setup code here, to run once:
}

void loop() {
  // put your main code here, to run repeatedly:
}