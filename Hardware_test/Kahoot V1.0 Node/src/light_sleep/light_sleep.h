#include "Arduino.h"
#include <ESP8266WiFi.h>

#define FPM_SLEEP_MAX_TIME 0xFFFFFFF

// Required for LIGHT_SLEEP_T delay mode
extern "C"
{
#include "user_interface.h"
#include "gpio.h"
}

class Light_sleep_helper
{
private:
    uint8_t _wake_up_pin;
    fpm_wakeup_cb _callback = NULL;
public:
    static Light_sleep_helper LightSleep;
    void light_sleep();
    void set_wake_up_pin(const uint8_t &wake_up_pin);
    void set_wakeup_callback(fpm_wakeup_cb cb);
};