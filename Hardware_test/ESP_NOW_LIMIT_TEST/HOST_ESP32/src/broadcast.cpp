#include "broadcast.h"

Led broadcastLED(2);

esp_err_t startBroadcast(const uint8_t *peer_addr,
                         const uint8_t *data,
                         size_t len,
                         size_t num,
                         size_t timeout)
{
    size_t counter = 0;
    Stopwatch<> timer;
    esp_err_t err = ESP_OK;
    bool (*checkCounter)(size_t counter, size_t num);
    checkCounter = (num == 0)
                       ? [](size_t, size_t) { return true; }
                       : [](size_t counter, size_t num) { return counter < num; };
    broadcastLED.blink(100);
    timer.start();

    while (timer.elapsed() <= timeout && checkCounter(counter, num))
    {
        err = esp_now_send(peer_addr, data, len);
        ++counter;
        broadcastLED.update();
        timer.start();
    }
    broadcastLED.off();
    return err;
}