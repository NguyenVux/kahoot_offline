#ifdef _DEBUG_
#include <Arduino.h>
#ifdef _BTSERIAL_
#include <BluetoothSerial.h>
#ifndef _BTSERIAL_OBJ_
#define _BTSERIAL_OBJ_
#endif
BluetoothSerial SerialBT;
#define PRINT(a) SerialBT.print(a)
#define PRINTLN(a) SerialBT.println(a)
#define PRINTF(a, ...) SerialBT.printf(a, __VA_ARGS__)
#else
#define PRINT(a) Serial.print(a)
#define PRINTLN(a) Serial.println(a)
#define PRINTF(a, ...) Serial.printf(a, __VA_ARGS__)
#endif // !_BTSERIAL_
#else
#define PRINT(a)
#define PRINTLN(a)
#define PRINTF(a, ...)
#endif // !_DEBUG_