#ifndef _ESP_NOW_BROADCAST_
#define _ESP_NOW_BROADCAST_
#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>
// #include "client.h"
#include "stopwatch.h"
#include "led.h"

#define DEFAULT_BROADCAST_TIMEOUT 100

/*
@brief Broadcast until time out or num is reached
@param num  How many retry to send data, 0 for unlimited retry
*/
esp_err_t startBroadcast(const uint8_t *peer_addr,
                         const uint8_t *data,
                         size_t len,
                         size_t num = 0,
                         size_t timeout = DEFAULT_BROADCAST_TIMEOUT);

#endif