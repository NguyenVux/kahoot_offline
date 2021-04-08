#ifndef _ESP_NOW_BROADCAST_
#define _ESP_NOW_BROADCAST_
#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>
#include "client.h"
#include "util.h"
#include "led.h"

#define DEFAULT_BROADCAST_TIMEOUT 1000
#define DEFAULT_SEND_NUM UINT32_MAX

/*
@brief Broadcast until timeout or num is reached
@param num  How many retries
@returns esp_err_t from esp_now_send
*/
esp_err_t startBroadcast(const uint8_t *peer_addr,
                         const uint8_t *data,
                         size_t len,
                         size_t num = DEFAULT_SEND_NUM,
                         size_t timeout = DEFAULT_BROADCAST_TIMEOUT);

#endif