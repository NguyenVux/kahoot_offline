#ifndef _ESP_NOW_BROADCAST_
#define _ESP_NOW_BROADCAST_
#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>
#include "client.h"
#include "stopwatch.h"
#include "led.h"

#define DEFAULT_BROADCAST_TIMEOUT 1000
#define DEFAULT_SEND_NUM 1

/*
@brief Broadcast until time out or num is reached
@param num  How many retry to send data
*/
esp_err_t startBroadcast(const uint8_t *peer_addr,
                         const uint8_t *data,
                         size_t len,
                         size_t num = DEFAULT_SEND_NUM,
                         size_t timeout = DEFAULT_BROADCAST_TIMEOUT);

#endif