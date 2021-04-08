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
    broadcastLED.blink(100);
    timer.start();
    while (timer.elapsed() <= timeout)
    {
        if (counter < num)
        {
            err = esp_now_send(peer_addr, data, len);
            ++counter;
        }
        broadcastLED.update();
    }
    broadcastLED.off();
    return err;
}