#ifndef _ESP_NOW_BROADCAST_
#define _ESP_NOW_BROADCAST_
#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>
// #include "client.h"
#include "stopwatch.h"
#include "led.h"

#define DEFAULT_BROADCAST_TIMEOUT 100

esp_err_t startBroadcast(const uint8_t *peer_addr,
                         const uint8_t *data,
                         size_t len,
                         size_t timeout = DEFAULT_BROADCAST_TIMEOUT,
                         size_t num = 1);

#endif