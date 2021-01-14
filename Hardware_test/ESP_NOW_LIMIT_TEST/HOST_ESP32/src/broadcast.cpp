#include "broadcast.h"

Led led(2);

esp_err_t startBroadcast(const uint8_t *peer_addr,
                         const uint8_t *data,
                         size_t len,
                         size_t timeout,
                         size_t num)
{
    size_t counter = 1;
    Stopwatch<> timer;
    esp_err_t err = ESP_OK;
    led.blink(100);
    timer.start();

    while (timer.elapsed() <= timeout && counter != num + 1)
    {
        err = esp_now_send(peer_addr, data, len);
        ++counter;
        led.update();
        timer.start();
    }
    led.off();
    return err;
}